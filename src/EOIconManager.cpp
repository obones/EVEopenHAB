/*
@file    EOIconManager.cpp
@brief   Contains the Icon manager definitions
@date    2021-09-17
@author  Olivier Sannier

@section LICENSE

MIT License

Copyright (c) 2021 Olivier Sannier

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <esp32HTTPrequest.h>
#include <EVE.h>

#include "EOIconManager.h"
#include "EOSettings.h"
#include "EOConstants.h"
#include "EODownloadManager.h"

#include "reload_color.png.h"

#define ICON_HEIGHT 64
#define ICON_WIDTH 64
#define ICON_BYTES_PER_PIXEL 2
#define ICON_BYTE_COUNT (ICON_WIDTH * ICON_HEIGHT * ICON_BYTES_PER_PIXEL)

// We are loading PNG files and the datasheet clearly states that the top 42K of RAM_G will be used as a temporary buffer
#define RAM_G_MAX_USABLE_ADDRESS (EVE_RAM_G + EVE_RAM_G_SIZE - 42*1024)
#define RAM_G_BOTTOM 0

namespace EVEopenHAB 
{
    IconManager::IconManager()
    {
        reloadIconAddress = RAM_G_MAX_USABLE_ADDRESS - reload_color_png_byte_count;
    }
    
    void IconManager::MainLoop()
    {
        if (!staticIconsLoaded)
        {
            EVE_cmd_loadimage(reloadIconAddress, EVE_OPT_NODL, reload_color_png, sizeof(reload_color_png));

            staticIconsLoaded = true;
        }

        startRetrieval();

        {        
            std::lock_guard<std::mutex> lock(recordsMutex);
            for (int recordIndex = 0; recordIndex < records.size(); recordIndex++)
            {
                iconRecord& record = records[recordIndex];

                switch (record.bitmapState)
                {
                    case BitmapState::Allocated:
                        if (record.buffer == nullptr)
                        {
                            /*Serial.print("Setting memory for ");
                            Serial.print(recordIndex);
                            Serial.print(" - address = ");
                            Serial.print(record.address);
                            Serial.print(" - byte count = ");
                            Serial.print(ICON_BYTE_COUNT);
                            Serial.println();*/

                            //EVE_cmd_memzero(record.address, ICON_BYTE_COUNT);
                            EVE_cmd_memset(record.address, 0xF0, ICON_BYTE_COUNT);
                            while (EVE_busy());
                            
                            record.bitmapState = BitmapState::Initialized;
                            break; 
                        }
                        // break is inside the test because if record.buffer is already available, we want to 
                        // fall through the call to load image, saving a useless call to memzero
                    case BitmapState::Initialized:
                        if (record.buffer != nullptr)
                        {
                            /*Serial.print("Loading image for ");
                            Serial.print(recordIndex);
                            Serial.print(" - address = ");
                            Serial.print(record.address);
                            Serial.println();*/

                            EVE_cmd_loadimage(record.address, EVE_OPT_NODL, record.buffer, record.bufferLength);
                            record.bitmapState = BitmapState::Loaded;

                            // Release memory now that the image is transferred to EVE, use a local reference to avoid having record.buffer point to deleted memory
                            uint8_t* buffer = record.buffer;
                            record.buffer = nullptr;
                            delete buffer;
                        }
                        break;
                    case BitmapState::Loaded:
                        break; // nothing, the image has already been transferred and loaded via LOADIMAGE
                }
            }
        }
    }

    void IconManager::Reset()
    {
        for (int recordIndex = 0; recordIndex < records.size(); recordIndex++)
        {
            iconRecord& record = records[recordIndex];
            delete(record.buffer);
        }
        records.clear();
    }

    IconManager* IconManager::Instance()
    {
        static IconManager instance;
        return &instance;
    }

    void iconRequestReadyStateChange(void* optParm, esp32HTTPrequest* request, int readyState)
    {
        if (readyState == 4)
        {
            /*Serial.println(F("Received a response, processing..."));
            Serial.print(F("  HTTP response code: "));
            Serial.println(request->responseHTTPcode());*/

            request->setDebug(false);

            IconManager* manager = static_cast<IconManager*>(optParm);
                
            if (request->responseHTTPcode() == 200)
            {
                Serial.println("Icon download success");

                std::lock_guard<std::mutex> lock(manager->recordsMutex);

                IconManager::iconRecord& record = manager->records[manager->indexBeingRetrieved];

                record.bufferLength = request->available();
                uint8_t *localBuffer = new byte[record.bufferLength];

                /*Serial.print(F("  For record "));
                Serial.print(manager->indexBeingRetrieved);
                Serial.print(F(" - name = "));
                Serial.print(record.name);
                Serial.println();
                Serial.print(F("  Buffer length = "));
                Serial.print(record.bufferLength);
                Serial.println();*/

                request->responseRead(localBuffer, record.bufferLength);

                record.buffer = localBuffer;
            }
            else
            {
                Serial.printf("Icon download failed: %d\r\n", request->responseHTTPcode());
            }

            manager->indexBeingRetrieved = -1;
        }
    }

    void IconManager::startRetrieval()
    {
        int recordIndex = 0;
        while (indexBeingRetrieved < 0 && recordIndex < records.size())
        {
            {
                std::lock_guard<std::mutex> lock(recordsMutex);

                iconRecord& record = records[recordIndex];
                if (record.buffer == nullptr && record.bitmapState < BitmapState::Loaded)
                {
                    //Serial.printf("--> no buffer for record, preparing request (%d will be %d)\r\n", indexBeingRetrieved, recordIndex);
                    indexBeingRetrieved = recordIndex;

                    String url = BASE_URL;
                    url += "/icon/";
                    url += record.name;
                    url += "?state=";
                    url += record.state;
                    url += "&format=png&iconset=";
                    url += ICON_SET_NAME;
                    
                    Serial.print("Requesting icon url = ");
                    Serial.println(url);

                    DownloadManager::Instance().Enqueue(url, iconRequestReadyStateChange, this);
                }
            }
            recordIndex++;
        }
    }

    int8_t IconManager::GetIconIndex(const char* name, const char* state)
    {
        /*Serial.print("Getting icon index for name = ");
        Serial.print(reinterpret_cast<uint32_t>(name));
        Serial.print(" - state = ");
        Serial.print(reinterpret_cast<uint32_t>(state));
        Serial.println();*/
        int8_t result = -1;
        {
            std::lock_guard<std::mutex> lock(recordsMutex);

            // Try to find a preexisting icon
            for (int recordIndex = 0; recordIndex < records.size(); recordIndex++)
            {
                iconRecord& record = records[recordIndex];
                if (strcmp(record.name, name) == 0 && strcmp(record.state, state) == 0)
                    return recordIndex + 1;
            } 

            // If not found, allocate a new one, downards from the top of RAM_G
            //uint32_t newAddress = RAM_G_MAX_USABLE_ADDRESS - ICON_BYTE_COUNT * (records.size() + 1);
            // If not found, allocate a new, upwards from the bottom of RAM_G
            uint32_t newAddress = RAM_G_BOTTOM + ICON_BYTE_COUNT * records.size();

            records.push_back( { .name = name, .state = state, .address = newAddress, .buffer = nullptr, .bufferLength = 0, .bitmapState = BitmapState::Allocated } );
            
            result = records.size();
        }

        startRetrieval();

        return result;
    }

    uint32_t IconManager::GetAddress(int8_t index)
    {
        std::lock_guard<std::mutex> lock(recordsMutex);
        if (index > 0 && index <= records.size())
        {
            iconRecord& record = records[index - 1];
            return record.address;
        }
        else
            return 0;
    }

    void IconManager::BurstIcon(int8_t index, int16_t x, int16_t y)
    {
        std::lock_guard<std::mutex> lock(recordsMutex);
        if (index > 0 && index <= records.size())
        {
            iconRecord& record = records[index - 1];

            /*Serial.print("Bursting icon ");
            Serial.print(index);
            Serial.print(" - address = ");
            Serial.print(record.address);
            Serial.print(" - at ");
            Serial.print(x);
            Serial.print(" ; ");
            Serial.print(y);
            Serial.println();*/

            EVE_cmd_dl_burst(BITMAP_HANDLE(index));
            EVE_cmd_dl_burst(BITMAP_LAYOUT(EVE_ARGB4, ICON_WIDTH * ICON_BYTES_PER_PIXEL, ICON_HEIGHT));
            EVE_cmd_dl_burst(BITMAP_SOURCE(record.address));
            EVE_cmd_dl_burst(BITMAP_SIZE(EVE_NEAREST, EVE_BORDER, EVE_BORDER, ICON_WIDTH, ICON_HEIGHT));
            EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
            EVE_cmd_dl_burst(COLOR_A(255));
            EVE_cmd_dl_burst(DL_BEGIN | EVE_BITMAPS);
            EVE_cmd_dl_burst(VERTEX2F(x, y));
            EVE_cmd_dl_burst(DL_END);
            EVE_cmd_dl_burst(BITMAP_HANDLE(0));
        }
    }

    uint32_t IconManager::GetReloadIconAddress() const
    {
        return reloadIconAddress;
    }

    void IconManager::BurstReloadIcon(int16_t x, int16_t y)
    {
        EVE_cmd_dl_burst(BITMAP_HANDLE(15));
        EVE_cmd_dl_burst(BITMAP_LAYOUT(reload_color_png_format, reload_color_png_width * reload_color_png_bytes_per_pixel, reload_color_png_height));
        EVE_cmd_dl_burst(BITMAP_SOURCE(reloadIconAddress));
        EVE_cmd_dl_burst(BITMAP_SIZE(EVE_NEAREST, EVE_BORDER, EVE_BORDER, reload_color_png_width, reload_color_png_height));
        EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
        EVE_cmd_dl_burst(COLOR_A(255));
        EVE_cmd_dl_burst(DL_BEGIN | EVE_BITMAPS);
        EVE_cmd_dl_burst(VERTEX2F(x, y));
        EVE_cmd_dl_burst(DL_END);
        EVE_cmd_dl_burst(BITMAP_HANDLE(0));
    }

}
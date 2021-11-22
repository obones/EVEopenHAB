/*
@file    EVEopenHAB.cpp
@brief   Contains main namespace definitions
@date    2021-08-18
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

#include <Arduino.h>
#include <sys/time.h>
#include <WiFi.h>
#include <WString.h>
#include <ArduinoJson.h>
#include "EVEopenHAB.h"
#include "EOConfig.h"
#include "EOWifi.h"
#include "EOSettings.h"
#include "EOHomepage.h"
#include "EOConstants.h"
#include "EOTouch.h"
#include "EOIconManager.h"
#include "EOFourthDimension.h"
#include "EODownloadManager.h"

#include <EVE.h>
#include <EVE_commands.h>
#include <EVE_target.h>
#include <EVE_config.h>

namespace EVEopenHAB
{
    struct timeval timeAtBoot;
    Homepage* homepage = nullptr;
    const unsigned long BAUD = 115200;            // 57600;      // Baudrate for serial communication.

    void Setup()
    {
        delay(250);         // Time needed to switch back from Upload to Console
        Serial.begin(BAUD); // Initialise the serial port

        Serial.setRxBufferSize(512);
        Serial.setTimeout(1);
        Serial.println(); // ESP "Garbage" message

        // EVE setup
        pinMode(EVE_CS, OUTPUT);
        digitalWrite(EVE_CS, HIGH);
        pinMode(EVE_PDN, OUTPUT);
        digitalWrite(EVE_PDN, LOW);

    	EVE_init_spi();

        if (EVE_init() != 0)
        {
            EVE_memWrite8(REG_PWM_DUTY, 0x30);	// setup backlight, range is from 0 = off to 0x80 = max 
            EVE_cmd_apilevel(2);  // BT817
            while (EVE_busy());    

            // background
            EVE_start_cmd_burst();
            EVE_cmd_dl_burst(CMD_DLSTART); // Start the display list 
            EVE_cmd_dl_burst(TAG(0)); // do not use the following objects for touch-detection 

            EVE_cmd_dl_burst(DL_CLEAR_RGB | WHITE);
            EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);

            // Black text
            EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
            EVE_cmd_text_burst(EVE_HSIZE / 2, EVE_VSIZE / 2, 31, EVE_OPT_CENTER, "EVEopenHAB");
            EVE_cmd_text_burst(EVE_HSIZE / 2, EVE_VSIZE / 2 + 30, 29, EVE_OPT_CENTERX, "Starting...");

            EVE_cmd_dl_burst(DL_DISPLAY); // put in the display list to mark its end
            EVE_cmd_dl_burst(CMD_SWAP); // tell EVE to use the new display list

            EVE_end_cmd_burst();
            
            while (EVE_busy());    
        }
        else
        {
            Serial.println("EVE_init failed");
        }

        if (gettimeofday(&timeAtBoot, NULL) != 0) 
            Serial.println(F("Failed to obtain time"));

        Serial.print(F("Arduino IDE Version :\t"));
        Serial.println(ARDUINO);

        Serial.print(F("ESP SDK version:\t"));
        Serial.println(ESP.getSdkVersion());

        Serial.print(F("Sketch File :\t\t"));
        Serial.println(F(__FILE__)); 
        Serial.println(F("Compiled on :\t\t" __DATE__ " at " __TIME__));

        EVEopenHAB::Config::Setup();

        //EVEopenHAB::Portal::Init();
        EVEopenHAB::Wifi::Setup();

        //EVEopenHAB::Portal::Start();

        EVEopenHAB::Touch::Setup();
    }

    bool requestSent = false;

    void requestReadyStateChange(void* optParm, esp32HTTPrequest* request, int readyState)
    {
        if (readyState == 4)
        {
            /*Serial.println(F("Received a response, processing..."));
            Serial.print(F("  HTTP response code: "));
            Serial.println(request->responseHTTPcode());*/
            request->setDebug(false);

            if (request->responseHTTPcode() == 200)
            {
                Serial.println("Sitemap download success");
                //Serial.println(request->available());

                String responseText = request->responseText();
                /*Serial.println(responseText.length());
                Serial.println(responseText);
                Serial.println();*/

                //Serial.println(F("Deserializing JSON"));
                StaticJsonDocument<2048> doc;

                DeserializationError error = deserializeJson(doc, responseText.c_str(), responseText.length());

                if (error) 
                {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.f_str());
                    requestSent = false;
                    return;
                }

                /*auto widgets = doc["homepage"]["widgets"].as<JsonArray>();
                int widgetIndex = 0;
                for (JsonArray::iterator it = widgets.begin(); it != widgets.end(); ++it)//(int widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++)
                {
                    Serial.print("Widget ");
                    Serial.print(widgetIndex);
                    Serial.print(": ");
                    Serial.println(it->as<JsonObject>()["label"].as<const char*>());
                    widgetIndex++;
                }*/

                IconManager::Instance()->Reset();

                if (homepage)
                {
                    // Use a local pointers to call delete so that the global pointer never points to a deleted object
                    Homepage* localHomepage = homepage;
                    homepage = nullptr;
                    delete localHomepage;
                }
                    
                homepage = new Homepage(doc["homepage"].as<JsonObject>());
                homepage->SetOnReloadTouched(
                    [=]()
                    {
                        requestSent = false;
                    }
                );
                homepage->SetReady();
                /*for (int widgetIndex = 0; widgetIndex < homepage->Widgets().size(); widgetIndex++)
                {
                    Serial.print("Widget ");
                    Serial.print(widgetIndex);
                    Serial.print(": ");
                    Serial.println(homepage->Widgets()[widgetIndex]->Label().c_str());
                }*/
            }
            else
            {
                Serial.printf("Sitemap download failed: %d\r\n", request->responseHTTPcode());
                requestSent = false;
            }
        }
    }

    static bool fourthDimension = false;

    void MainLoop()
    {
        EVEopenHAB::Wifi::MainLoop();
        //OTA::mainLoop();

        if ((WiFi.status() == WL_CONNECTED) && !requestSent)
        {
            requestSent = true;

            // Display a spinner until we have received the sitemap
            EVE_start_cmd_burst();
            EVE_cmd_dl_burst(CMD_DLSTART); 
            EVE_cmd_dl_burst(DL_CLEAR_RGB | WHITE);
            EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
            EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
            EVE_cmd_text_burst(EVE_HSIZE / 2, EVE_VSIZE / 4, 29, EVE_OPT_CENTERX, "Waiting for sitemap...");
            EVE_cmd_spinner_burst(EVE_HSIZE / 2, EVE_VSIZE / 2, 0, 0);
            EVE_end_cmd_burst();
            while (EVE_busy());    

            Serial.println(F("Requesting the sitemap"));
            DownloadManager::Instance().Enqueue(SitemapURL, requestReadyStateChange, nullptr);
        }

        if (EVEopenHAB::Touch::MainLoop())
        {
            EVEopenHAB::FourthDimension::Enter();
            fourthDimension = true;
        }

        if (fourthDimension)
        {
            if (!EVEopenHAB::FourthDimension::MainLoop())
            {
                fourthDimension = false;
                requestSent = false;
            }
        }
        else
        {
            EVEopenHAB::IconManager::Instance()->MainLoop();

            // homepage display
            if (homepage && homepage->IsDirty() && homepage->IsReady())
            {
                homepage->LayoutChildren();
                homepage->Render();
            }
        }
    }
}
/*
@file    EOTouch.cpp
@brief   Contains Touch management definitions
@date    2021-09-14
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
#include <LITTLEFS.h>
#include <EVE.h>
#include "EOTagManager.h"
#include "EOConstants.h"

namespace EVEopenHAB 
{
    namespace Touch
    {
        void Setup()
        {
            EVE_memWrite8(REG_TOUCH_MODE, 0b11); // touch engine activated

            // look for saved touch calibration values, if it does not exist, call the calibration widget and create the file
            Serial.println("Looking for touch calibration values");
            const char TouchFileName[] = "/touch.bin";
            if (LITTLEFS.exists(TouchFileName))
            {
                Serial.println("Calibration file found, using directly");
                File file = LITTLEFS.open(TouchFileName, "r");
                uint32_t regValue;

                file.read(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                EVE_memWrite32(REG_TOUCH_TRANSFORM_A, regValue);

                file.read(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                EVE_memWrite32(REG_TOUCH_TRANSFORM_B, regValue);

                file.read(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                EVE_memWrite32(REG_TOUCH_TRANSFORM_C, regValue);

                file.read(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                EVE_memWrite32(REG_TOUCH_TRANSFORM_D, regValue);

                file.read(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                EVE_memWrite32(REG_TOUCH_TRANSFORM_E, regValue);

                file.read(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                EVE_memWrite32(REG_TOUCH_TRANSFORM_F, regValue);
                file.close();
            }
            else
            {
                Serial.println("Calibration file not found, forcing calibration");
                EVE_memWrite8(REG_CTOUCH_EXTENDED, 1); // force compatibility mode for calibration

                EVE_cmd_dl(CMD_DLSTART); // Start the display list 

                EVE_cmd_dl(DL_CLEAR_RGB | WHITE);
                EVE_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);

                EVE_cmd_dl(DL_COLOR_RGB | BLACK);
                EVE_cmd_text(EVE_HSIZE / 2, EVE_VSIZE / 2, 31, EVE_OPT_CENTER, "EVEopenHAB");
                EVE_cmd_text(EVE_HSIZE / 2, EVE_VSIZE / 2 + 30, 29, EVE_OPT_CENTERX, "Calibrating touch screen, please tap on the dots");
                EVE_cmd_calibrate();
                EVE_cmd_dl(DL_DISPLAY); 
                EVE_cmd_dl(CMD_SWAP);
                while (EVE_busy());

                File file = LITTLEFS.open(TouchFileName, "w");
                uint32_t regValue;

                regValue = EVE_memRead32(REG_TOUCH_TRANSFORM_A);
                file.write(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));

                regValue = EVE_memRead32(REG_TOUCH_TRANSFORM_B);
                file.write(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                
                regValue = EVE_memRead32(REG_TOUCH_TRANSFORM_C);
                file.write(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                
                regValue = EVE_memRead32(REG_TOUCH_TRANSFORM_D);
                file.write(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                
                regValue = EVE_memRead32(REG_TOUCH_TRANSFORM_E);
                file.write(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                
                regValue = EVE_memRead32(REG_TOUCH_TRANSFORM_F);
                file.write(reinterpret_cast<uint8_t*>(&regValue), sizeof(regValue));
                
                file.close();
            }

            EVE_memWrite8(REG_CTOUCH_EXTENDED, 0); // Extended mode

            while (EVE_busy());    
        }

        void MainLoop()
        {
            uint32_t current_millis = millis();
            static uint32_t previous_millis = 0;

            if((current_millis - previous_millis) > 4) // execute the code every 5 milli-seconds
            {
                previous_millis = current_millis;

                if (!EVE_busy()) // is EVE still processing the last display list? 
                {
                    static uint8_t previousTag = 0;
                    static uint16_t previousTrackedValue = 0;

                    uint8_t tag = 0;
                    uint16_t trackedValue = 0;

                    uint32_t trackerInfo = EVE_memRead32(REG_TRACKER); // read the first tracker
                    if (trackerInfo)    
                    {
                        tag = trackerInfo & 0xFF;
                        trackedValue = trackerInfo >> 16;
                    }
                    else
                    {
                        tag = EVE_memRead8(REG_TOUCH_TAG); // read the value for the first touch point 
                    }                

                    /*if (tag)
                    {
                        Serial.print("Found touch, tag = ");
                        Serial.print(tag);
                        Serial.print(" - trackedValue = ");
                        Serial.println(trackedValue);
                    }*/

                    if (previousTag != tag)
                        TagManager::Instance()->Invoke(previousTag, previousTrackedValue);

                    previousTag = tag;
                    previousTrackedValue = trackedValue;
                }
            }
        }
    }
}

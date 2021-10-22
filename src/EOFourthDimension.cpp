/*
@file    EOFourthDimension.cpp
@brief   Contains Fourth dimension definitions
@date    2021-10-04
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
    namespace FourthDimension
    {
        void EVE_cmd_newlist_burst(uint32_t adr)
        {
            spi_transmit_burst(CMD_NEWLIST);
            spi_transmit_burst(adr);
        }

        void Enter()
        {
            typedef struct {
                int16_t X;
                int16_t Y;
                int16_t deltaX;
                int16_t deltaY;
            } starInfo;
            
            starInfo stars[6] = 
                { 
                    { .X = EVE_HSIZE / 5, .Y = EVE_VSIZE / 3, .deltaX = +10, .deltaY = -4 },
                    { .X = (3 * EVE_HSIZE) / 5, .Y = (2 * EVE_VSIZE) / 3, .deltaX = +20, .deltaY = +5 },
                    { .X = (4 * EVE_HSIZE) / 5, .Y = EVE_VSIZE / 3, .deltaX = -20, .deltaY = -4 },
                    { .X = (2 * EVE_HSIZE) / 5, .Y = (2 * EVE_VSIZE) / 3, .deltaX = +15, .deltaY = 0 },
                    { .X = EVE_HSIZE / 7, .Y = EVE_VSIZE / 6, .deltaX = 0, .deltaY = -8 },
                    { .X = (3 * EVE_HSIZE) / 7, .Y = (7 * EVE_VSIZE) / 9, .deltaX = -9, .deltaY = -4 },
                };
            const int starsCount = sizeof(stars) / sizeof(starInfo);
            const uint32_t BASE_LIST_ADDR = EVE_RAM_G + 0;
            const uint32_t STAR_LIST_ADDR = EVE_RAM_G + 0x100;

            // The display list never changes, only the stars coordinates. To avoid sending the entire list
            // at each refresh, we use two display lists (BT817 specific):
            // The first only contains the stars VERTEX2F orders and a CMD_RETURN
            // The second contains the static part of the display list (background + text)
            EVE_start_cmd_burst();
            EVE_cmd_newlist_burst(STAR_LIST_ADDR);
            for (int starIndex = 0; starIndex < starsCount; starIndex ++)
                EVE_cmd_dl_burst(VERTEX2F(stars[starIndex].X, stars[starIndex].Y));
            EVE_cmd_dl_burst(CMD_ENDLIST);
            EVE_end_cmd_burst();
            while (EVE_busy());

            EVE_start_cmd_burst();
            EVE_cmd_newlist_burst(BASE_LIST_ADDR);
        	EVE_cmd_dl_burst(VERTEX_FORMAT(0)); 
            EVE_cmd_dl_burst(DL_CLEAR_RGB | BLACK);
            EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
            EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
            EVE_cmd_text_burst(EVE_HSIZE / 2, EVE_VSIZE / 2, 24, EVE_OPT_CENTERX, "Entering the fourth dimension...");
            EVE_cmd_dl_burst(POINT_SIZE(32));
            EVE_cmd_dl_burst(DL_BEGIN | EVE_POINTS);
            EVE_cmd_calllist_burst(STAR_LIST_ADDR);
            EVE_cmd_dl_burst(DL_END);
            EVE_cmd_dl_burst(CMD_ENDLIST);
            EVE_end_cmd_burst();
            while (EVE_busy());

            EVE_memWrite32(REG_SOUND, 0x14);
            EVE_memWrite32(REG_VOL_SOUND, 0xFF);
            EVE_memWrite32(REG_PLAY, 0x01);

            uint32_t starsRAMAddress = STAR_LIST_ADDR;
            Serial.printf("starsRAMAddress = %x", starsRAMAddress);
            Serial.println();

            for (int stepIndex = 0; stepIndex < 70; stepIndex++)
            {
                // We would have loved for the BT817 to read its instructions directly from RAM_G when using call lists
                // While it does that just fine with bitmaps content, it seems its importing the display items from
                // RAM_G when the list is swapped. 
                // Using a "static" display list that calls the variable one allows us to simply send the CMD_CALLLIST
                // at each step of the animation.
                EVE_start_cmd_burst();
                EVE_cmd_dl_burst(CMD_DLSTART); 
                EVE_cmd_calllist_burst(BASE_LIST_ADDR);
                EVE_cmd_dl_burst(DL_DISPLAY);
                EVE_cmd_dl_burst(CMD_SWAP);

                EVE_end_cmd_burst();
                while (EVE_busy());

                usleep(50 * 1000);

                // Move the stars to their next position
                for (int starIndex = 0 ; starIndex < starsCount; starIndex++)
                {
                    stars[starIndex].X += stars[starIndex].deltaX;
                    stars[starIndex].Y += stars[starIndex].deltaY;

                    Serial.print("Writing star ");
                    Serial.print(starIndex);
                    Serial.print(" (");
                    Serial.print(stars[starIndex].X);
                    Serial.print("; ");
                    Serial.print(stars[starIndex].Y);
                    Serial.printf(") at address %x", starsRAMAddress + starIndex * sizeof(int32_t));
                    Serial.println();

                    EVE_memWrite32(starsRAMAddress + starIndex * sizeof(int32_t), VERTEX2F(stars[starIndex].X, stars[starIndex].Y));
                }
            }
        }

        bool MainLoop()
        {
            bool result = true;
            uint32_t current_millis = millis();
            static uint32_t previous_millis = 0;

            if((current_millis - previous_millis) > 4) // execute the code every 5 milli-seconds
            {
                previous_millis = current_millis;
            }

            return result;
        }
    }
}

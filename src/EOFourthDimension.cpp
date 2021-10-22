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
            EVE_start_cmd_burst();
            EVE_cmd_dl_burst(CMD_DLSTART); 
        	EVE_cmd_dl_burst(VERTEX_FORMAT(0)); 
            EVE_cmd_dl_burst(DL_CLEAR_RGB | BLACK);
            EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
            EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
            EVE_cmd_text_burst(EVE_HSIZE / 2, EVE_VSIZE / 2, 24, EVE_OPT_CENTERX, "Entering the fourth dimension...");
            EVE_cmd_dl_burst(POINT_SIZE(32));
            EVE_cmd_dl_burst(DL_BEGIN | EVE_POINTS);
            EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE / 5, EVE_VSIZE / 3));
            EVE_cmd_dl_burst(VERTEX2F((3 * EVE_HSIZE) / 5, (2 * EVE_VSIZE) / 3));
            EVE_cmd_dl_burst(VERTEX2F((4 * EVE_HSIZE) / 5, (EVE_VSIZE / 3)));
            EVE_cmd_dl_burst(VERTEX2F((2 * EVE_HSIZE) / 5, (2 * EVE_VSIZE) / 3));
            EVE_cmd_dl_burst(VERTEX2F(EVE_HSIZE / 7, EVE_VSIZE / 6));
            EVE_cmd_dl_burst(VERTEX2F((3 * EVE_HSIZE) / 7, (7 * EVE_VSIZE) / 9));
            EVE_cmd_dl_burst(DL_END);

            EVE_cmd_dl_burst(DL_DISPLAY);
            EVE_cmd_dl_burst(CMD_SWAP); // tell EVE to use the new display list

            EVE_end_cmd_burst();
            while (EVE_busy());    

            EVE_memWrite32(REG_SOUND, 0x14);
            EVE_memWrite32(REG_VOL_SOUND, 0xFF);
            EVE_memWrite32(REG_PLAY, 0x01);
            sleep(5);
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

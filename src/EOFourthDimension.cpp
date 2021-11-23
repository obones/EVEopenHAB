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
#include "grass16x16-png8.png.h"
#include "mole64x48-png8.png.h"

namespace EVEopenHAB 
{
    namespace FourthDimension
    {
        void EVE_cmd_newlist_burst(uint32_t adr)
        {
            spi_transmit_burst(CMD_NEWLIST);
            spi_transmit_burst(adr);
        }

        /* -------- RAM Layout -------

            The mole game uses various graphic elements stored in RAM_G so we must make sure they don't overlap
            This is why it is a good idea to have this RAM map describing what gets stored and where.

            Offset   Usage
            0x0000   Grass sprite
            0x0200   Mole sprite
            0x0400   Mole coordinates display list
            0x0410   Static display list
        */

        const uint32_t GRASS_BITMAP = EVE_RAM_G + 0x0000;
        const uint32_t MOLE_BITMAP = EVE_RAM_G + 0x0200;
        const uint32_t MOLE_COORDINATES_DL = EVE_RAM_G + 0x0400;
        const uint32_t STATIC_DL = EVE_RAM_G + 0x0410;
        const uint32_t TEXT_COLOR = 0xBB2200;

        // Bitmap handles 16 to 31 are reserved, 1 to 15 have to be managed by us
        const uint8_t GrassBitmapHandle = 13;
        const uint8_t MoleBitmapHandle = 12;
        const uint8_t Font34BitmapHandle = 11;

        typedef struct 
        {
            int16_t MoleX, MoleY;
            int32_t TimeBeforeChange;
            int32_t NextTimeBetweenChange;
            int32_t Score;
            int8_t LivesLeft;
            bool ContinueToPlay;
        } GameState;
        const GameState StartGameState = { .MoleX = EVE_HSIZE / 2, .MoleY = EVE_VSIZE / 2, .TimeBeforeChange = 3000, .NextTimeBetweenChange = 3000, .Score = 0, .LivesLeft = 3, .ContinueToPlay = true};

        GameState gameState = StartGameState;
        uint32_t previous_millis = 0;

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

                    /*Serial.print("Writing star ");
                    Serial.print(starIndex);
                    Serial.print(" (");
                    Serial.print(stars[starIndex].X);
                    Serial.print("; ");
                    Serial.print(stars[starIndex].Y);
                    Serial.printf(") at address %x", starsRAMAddress + starIndex * sizeof(int32_t));
                    Serial.println();*/

                    EVE_memWrite32(starsRAMAddress + starIndex * sizeof(int32_t), VERTEX2F(stars[starIndex].X, stars[starIndex].Y));
                }
            }

            // Now that the stars are gone, we can load the game images.
            // Using the BT817 specific CMD_GETIMAGE makes it much easier to retrieve the image and palette
            // addresses that will have to be used later on when rendering them.
            uint32_t GrassSourceAddr;
            uint32_t GrassPaletteAddr;
            uint32_t MoleSourceAddr;
            uint32_t MolePaletteAddr;
            uint32_t dummy;
            
            EVE_cmd_loadimage(GRASS_BITMAP, EVE_OPT_NODL, grass_png, sizeof(grass_png));
            EVE_cmd_getimage(&GrassSourceAddr, &dummy, &dummy, &dummy, &GrassPaletteAddr);

            EVE_cmd_loadimage(MOLE_BITMAP, EVE_OPT_NODL, mole_png, sizeof(mole_png));
            EVE_cmd_getimage(&MoleSourceAddr, &dummy, &dummy, &dummy, &MolePaletteAddr);

            TagManager::Instance()->Reset();

            // As above with the stars, we create display list that simply places the mole sprite
            EVE_start_cmd_burst();
            EVE_cmd_newlist_burst(MOLE_COORDINATES_DL);
            EVE_cmd_dl_burst(VERTEX2F(0, 0));
            EVE_cmd_dl_burst(CMD_ENDLIST);

            // We also create a "static" display list that gets all the commands that never change from one iteration to the next
            // This saves a lot of bandwidth on the SPI bus
            EVE_cmd_newlist_burst(STATIC_DL);
            EVE_cmd_dl_burst(CMD_DLSTART); 
            EVE_cmd_dl_burst(TAG(0)); 
            EVE_cmd_dl_burst(VERTEX_FORMAT(0));

            EVE_cmd_dl_burst(BITMAP_HANDLE(GrassBitmapHandle));
            EVE_cmd_dl_burst(BITMAP_LAYOUT(grass_png_format, grass_png_width * grass_png_bytes_per_pixel, grass_png_height));
            EVE_cmd_dl_burst(BITMAP_SOURCE(GrassSourceAddr));
            EVE_cmd_dl_burst(PALETTE_SOURCE(GrassPaletteAddr));
            EVE_cmd_dl_burst(BITMAP_SIZE(EVE_NEAREST, EVE_REPEAT, EVE_REPEAT, EVE_HSIZE, EVE_VSIZE));
            EVE_cmd_dl_burst(BITMAP_SIZE_H(EVE_HSIZE, EVE_VSIZE));
            EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
            EVE_cmd_dl_burst(COLOR_A(255));
            EVE_cmd_dl_burst(DL_BEGIN | EVE_BITMAPS);
            EVE_cmd_dl_burst(VERTEX2F(0, 0));
            EVE_cmd_dl_burst(DL_END);
            EVE_cmd_dl_burst(BITMAP_HANDLE(0));
            EVE_cmd_dl_burst(DL_COLOR_RGB | TEXT_COLOR);
            EVE_cmd_text_burst(5, 5, 29, 0, "Lives");
            EVE_cmd_text_burst(EVE_HSIZE - 10, 5, 29, EVE_OPT_RIGHTX, "Score");

            static uint8_t MoleTag = TagManager::Instance()->GetNextTag(
                [&](uint8_t tag, uint16_t trackedValue) 
                {
                    // mole has been touched, award some points
                    gameState.Score += 100 + gameState.TimeBeforeChange / 10;

                    // hide the mole for half the timer time
                    gameState.MoleY = -2 * mole_png_height;
                    gameState.TimeBeforeChange = gameState.NextTimeBetweenChange / 2;  
                }
            );
            EVE_cmd_dl_burst(TAG(MoleTag)); 
            EVE_cmd_dl_burst(BITMAP_HANDLE(MoleBitmapHandle));
            EVE_cmd_dl_burst(BITMAP_LAYOUT(mole_png_format, mole_png_width * mole_png_bytes_per_pixel, mole_png_height));
            EVE_cmd_dl_burst(BITMAP_SOURCE(MoleSourceAddr));
            EVE_cmd_dl_burst(PALETTE_SOURCE(MolePaletteAddr));
            EVE_cmd_dl_burst(BITMAP_SIZE(EVE_NEAREST, EVE_BORDER, EVE_BORDER, mole_png_width, mole_png_height));
            EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
            EVE_cmd_dl_burst(COLOR_A(255));
            EVE_cmd_dl_burst(DL_BEGIN | EVE_BITMAPS);
            EVE_cmd_calllist_burst(MOLE_COORDINATES_DL);
            EVE_cmd_dl_burst(DL_END);
            EVE_cmd_dl_burst(BITMAP_HANDLE(0));
            EVE_cmd_dl_burst(TAG(0)); 
            EVE_cmd_dl_burst(CMD_ENDLIST);

            EVE_end_cmd_burst();
            while (EVE_busy());

            gameState = StartGameState;
            previous_millis = 0;
        }

        bool MainLoop()
        {
            uint32_t current_millis = millis();
            static bool logLivesLeft = false;

            if((current_millis - previous_millis) > 4) // execute the code every 5 milli-seconds
            {
                if (previous_millis > 0)
                    gameState.TimeBeforeChange -= current_millis - previous_millis;
                previous_millis = current_millis;

                // Update mole coordinates
                EVE_memWrite32(MOLE_COORDINATES_DL, VERTEX2F(gameState.MoleX, gameState.MoleY));

                // Burst the periodic display list, that calls the RAM based static display list
                EVE_start_cmd_burst();
                EVE_cmd_dl_burst(CMD_DLSTART); 
                EVE_cmd_dl_burst(TAG(0)); 
                EVE_cmd_dl_burst(VERTEX_FORMAT(0));
                EVE_cmd_calllist_burst(STATIC_DL);

                // Write lives left and score
                EVE_cmd_dl_burst(DL_COLOR_RGB | TEXT_COLOR);
                EVE_cmd_number_burst(5, 30, 29, 0, gameState.LivesLeft);
                EVE_cmd_number_burst(EVE_HSIZE - 10, 30, 29, EVE_OPT_RIGHTX, gameState.Score);
                
                // Are we still alive?
                if (logLivesLeft)
                    Serial.println(gameState.LivesLeft);
                if (gameState.LivesLeft > 0)
                {
                    logLivesLeft = false;
                    // Did timer elapse?
                    if ((gameState.TimeBeforeChange <= 0))
                    {
                        Serial.println("Timer has elapsed");
                        // Is the mole hiding?
                        if (gameState.MoleY < 0)
                        {
                            // yes, make it come back, reset the timer to the next display time, and accelerate the game
                            gameState.MoleX = random(10, EVE_HSIZE - mole_png_width - 10);
                            gameState.MoleY = random(10, EVE_VSIZE - mole_png_height - 10);
                            gameState.TimeBeforeChange = gameState.NextTimeBetweenChange;
                            gameState.NextTimeBetweenChange -= gameState.NextTimeBetweenChange / 10; 
                        }
                        else
                        {
                            // no, the mole has won, remove one life, hide the mole for two seconds
                            gameState.LivesLeft--;
                            gameState.MoleY = -2 * mole_png_height;
                            gameState.TimeBeforeChange = 2000;  
                        }
                    }
                }
                else
                {
                    EVE_cmd_romfont_burst(Font34BitmapHandle, 34);
                    EVE_cmd_dl_burst(DL_COLOR_RGB | 0xDDBB22);
                    EVE_cmd_text_burst(EVE_HSIZE / 2, 50, Font34BitmapHandle, EVE_OPT_CENTERX, "You lost!");

                    static uint8_t retryTag = 
                        TagManager::Instance()->GetNextTag(
                            [&](uint8_t tag, uint16_t trackedValue) 
                            {
                                Serial.print("Reseting game state from ");
                                Serial.print(gameState.LivesLeft);
                                Serial.print(" lives to ");
                                Serial.print(StartGameState.LivesLeft);
                                gameState = StartGameState;
                                Serial.print(" - now ");
                                Serial.print(gameState.LivesLeft);
                                Serial.println();
                                logLivesLeft = true;
                            }
                        );
                    EVE_cmd_dl_burst(TAG(retryTag)); 
                    EVE_cmd_text_burst(EVE_HSIZE / 2, EVE_VSIZE / 2, 30, EVE_OPT_CENTERX, "Retry");

                    static uint8_t exitTag = 
                        TagManager::Instance()->GetNextTag(
                            [&](uint8_t tag, uint16_t trackedValue) 
                            {
                                Serial.print("Setting ContinueToPlay from ");
                                Serial.print((gameState.ContinueToPlay) ? "true" : "false");
                                Serial.print(" to false ");
                                gameState.ContinueToPlay = false;
                                Serial.print(" - now ");
                                Serial.print((gameState.ContinueToPlay) ? "true" : "false");
                                Serial.println();
                            }
                        );
                    EVE_cmd_dl_burst(TAG(exitTag)); 
                    EVE_cmd_text_burst(EVE_HSIZE / 2, EVE_VSIZE / 2 + 50, 30, EVE_OPT_CENTERX, "Exit");

                    EVE_cmd_dl_burst(TAG(0)); 
                }

                EVE_cmd_dl_burst(DL_DISPLAY);
                EVE_cmd_dl_burst(CMD_SWAP);

                EVE_end_cmd_burst();
                while (EVE_busy());
            }

            if (logLivesLeft)
                Serial.print((gameState.ContinueToPlay) ? "true" : "false");
            return gameState.ContinueToPlay;
        }
    }
}

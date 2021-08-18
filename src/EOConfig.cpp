/*
@file    Config.cpp
@brief   Contains Config definitions
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
#include <FS.h>
#include <LITTLEFS.h>
#include "EOConfig.h"

namespace EVEopenHAB 
{
    namespace Config
    {
        void Setup()
        {
            Serial.print(F("Loading persistent filesystem... "));

            if (!LITTLEFS.begin(true))
            {
                Serial.println(F(" FAILED!!"));
                return;
            }
            Serial.print(F("OK. "));

            Serial.printf_P(PSTR("File system usage: %u/%uKB.\r\n"), LITTLEFS.usedBytes() / 1024, LITTLEFS.totalBytes() / 1024);

        }
    }
}

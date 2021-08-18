/*
@file    Wifi.cpp
@brief   Contains Wifi definitions
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
#include <Wifi.h>
#include "EOWifi.h"

namespace EVEopenHAB 
{
    namespace Wifi
    {
        void Setup()
        {
            WiFi.onEvent(eventHandler_WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
            WiFi.onEvent(eventHandler_WiFiStationGotIp, SYSTEM_EVENT_STA_GOT_IP);
            WiFi.onEvent(eventHandler_WiFiStationLostIp, SYSTEM_EVENT_STA_LOST_IP);
        }

        void MainLoop()
        {
            
        }
    }
}

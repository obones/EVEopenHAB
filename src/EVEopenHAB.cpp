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
#include <asyncHTTPrequest.h>
#include <WString.h>
#include <ArduinoJson.h>
#include "EVEopenHAB.h"
#include "EOConfig.h"
#include "EOWifi.h"
#include "EOSettings.h"

namespace EVEopenHAB
{
    struct timeval timeAtBoot;
    const unsigned long BAUD = 115200;            // 57600;      // Baudrate for serial communication.

    void Setup()
    {
        delay(250);         // Time needed to switch back from Upload to Console
        Serial.begin(BAUD); // Initialise the serial port

        Serial.setRxBufferSize(512);
        Serial.setTimeout(1);

        if (gettimeofday(&timeAtBoot, NULL) != 0) 
            Serial.println(F("Failed to obtain time"));

        Serial.println(); // ESP "Garbage" message
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
    }

    void requestReadyStateChange(void* optParm, asyncHTTPrequest* request, int readyState)
    {
        if (readyState == 4)
        {
            Serial.println(F("Received a response, processing..."));
            Serial.print(F("  HTTP response code: "));
            Serial.println(request->responseHTTPcode());

            String responseText = request->responseText();
            Serial.println(responseText);
            Serial.println();
            request->setDebug(false);

            if (request->responseHTTPcode() == 200)
            {
                Serial.println(F("Deserializing JSON"));
                StaticJsonDocument<96> doc;

                DeserializationError error = deserializeJson(doc, responseText.c_str(), responseText.length());

                if (error) 
                {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.f_str());
                    return;
                }
            }
        }
    }    

    bool requestSent = false;

    void MainLoop()
    {
        EVEopenHAB::Wifi::MainLoop();
        //OTA::mainLoop();

        if ((WiFi.status() == WL_CONNECTED) && !requestSent)
        {
            Serial.println(F("Requesting the sitemap"));
            asyncHTTPrequest request;
            request.setDebug(true);
            request.onReadyStateChange(requestReadyStateChange);
            request.open("GET", SitemapURL);
            request.send();

            requestSent = true;
        }
    }
}
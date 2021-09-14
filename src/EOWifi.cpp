/*
@file    EOWifi.cpp
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
#include <WString.h>
#include <time.h>
#include "EVEopenHAB.h"
#include "EOWifi.h"
#include "EOParams.h"
#include "EOSettings.h"

namespace EVEopenHAB 
{
    namespace Wifi
    {
        namespace params {

            String client_ssid = WIFI_SSID;
            String client_password = WIFI_PASSWORD;

            bool client_dhcp_enabled = WIFI_USE_DHCP;
            String client_ip = WIFI_STATIC_IP;
            String client_mask = WIFI_STATIC_MASK;
            String client_gateway = WIFI_STATIC_GATEWAY;
            String client_dns = WIFI_STATIC_DNS;
            String client_hostname = WIFI_DHCP_NAME;
        }

        void resetClientWifi() 
        {
            // We start by connecting to a WiFi network
            Serial.print(F("Trying to connect WIFI SSID "));
            Serial.print(params::client_ssid.c_str());
            Serial.println(F(". A status will be given whenever it occurs."));

            WiFi.setHostname(params::client_hostname.c_str());

            if (!params::client_dhcp_enabled) 
            {
                IPAddress ip, gateway, mask, dns;

                ip.fromString(params::client_ip);
                gateway.fromString(params::client_gateway);
                mask.fromString(params::client_mask);
                dns.fromString(params::client_dns);

                WiFi.config(ip, gateway, mask, dns );

            } 
            else 
            {
                WiFi.config(IPAddress((uint32_t) 0), IPAddress((uint32_t) 0), IPAddress((uint32_t) 0));
            }

            delay(500);
            if (!WiFi.isConnected() || WiFi.SSID() != params::client_ssid) {
                WiFi.begin(params::client_ssid.c_str(), params::client_password.c_str());
            }

            WiFi.setAutoConnect(true);
            WiFi.setAutoReconnect(true);
        }

        void start_WIFI()
        {
            WiFi.mode(WIFI_STA);

            // just in case it
            WiFi.softAPdisconnect();

            resetClientWifi();
        }

        void printLocalTime(struct timeval *newTime = nullptr)
        {
            struct tm tmp;
            struct tm *timeinfo;

            if (newTime == nullptr) 
            {
                if (!getLocalTime(&tmp))
                {
                    Serial.println(F("Failed to obtain time"));
                    return;
                }
                timeinfo = &tmp;
            }
            else 
            {
                timeinfo = localtime(&newTime->tv_sec);
            }

            Serial.printf_P(
                PSTR("Current time is %04i-%02i-%02i %02i:%02i:%02i\r\n"),
                timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday,
                timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec
            );
        }

        void ntpUpdateCallback(struct timeval *newTime)
        {
            if (timeAtBoot.tv_sec < 10000 ) 
            {
                timeAtBoot.tv_sec = newTime->tv_sec - 10;
                printLocalTime(newTime);
            }
        }
        void reconnectServices() 
        {
            // in case NTP forces a time drift we need to recalculate timeAtBoot
            sntp_set_time_sync_notification_cb(ntpUpdateCallback);

            configTzTime("UTC", EVEopenHAB::Params::NTPServer.c_str());
        }

        void eventHandler_WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) 
        {

            Serial.print(F("Connected to AP SSID:"));
            for(int i = 0; i < info.connected.ssid_len; i++)
                Serial.print((char) info.connected.ssid[i]);

            Serial.print("  BSSID: ");
            for(int i = 0; i < 6; i++)
            {
                Serial.printf("%02X", info.connected.bssid[i]);

                if (i < 5)
                    Serial.print(":");
            }

            Serial.print(F("  Channel: "));
            Serial.print(info.connected.channel);

            Serial.print(F("  Auth mode: "));
            Serial.println(info.connected.authmode);
        }

        void eventHandler_WiFiStationGotIp(WiFiEvent_t event, WiFiEventInfo_t info) 
        {
            Serial.printf_P(PSTR("WiFi Client has received a new IP: %s\r\n"), WiFi.localIP().toString().c_str());
            reconnectServices();
        }

        void eventHandler_WiFiStationLostIp(WiFiEvent_t event, WiFiEventInfo_t info) 
        {
            Serial.println("WiFi Client has lost its IP");
        }

        void Setup()
        {
            WiFi.onEvent(eventHandler_WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
            WiFi.onEvent(eventHandler_WiFiStationGotIp, SYSTEM_EVENT_STA_GOT_IP);
            WiFi.onEvent(eventHandler_WiFiStationLostIp, SYSTEM_EVENT_STA_LOST_IP);

            WiFi.setTxPower(WIFI_POWER_11dBm);

            start_WIFI();
        }

        void MainLoop()
        {
            WiFi.enableAP(false);
        }
    }
}

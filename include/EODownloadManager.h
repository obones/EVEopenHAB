/*
@file    EODownloadManager.h
@brief   Contains the download manager declarations
@date    2021-11-19
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
#ifndef EODOWNLOADMANAGER_H
#define EODOWNLOADMANAGER_H

#include <Arduino.h>
#include <esp32HTTPrequest.h>

#include "EOSafeQueue.h"

namespace EVEopenHAB 
{
    //esp32HTTPrequest https://github.com/boblemaire/esp32HTTPrequest
    //https://www.codeproject.com/Articles/5295781/Use-Both-Cores-on-an-ESP32-Easy-Synchronization-wi

    class DownloadManager
    {
        private:
            typedef std::function<void(void*, esp32HTTPrequest*, int readyState)> readyStateChangeCB;

            typedef struct
            {
                String URL;
                readyStateChangeCB Callback;
                void* Parameter;
            } downloadRecord;

            SafeQueue<downloadRecord> downloadQueue;

            DownloadManager();

            friend void downloadTask(void * managerPtr);
        public:
            void Enqueue(String url, readyStateChangeCB callback, void* optParm);

            static DownloadManager& Instance();
    };
}

#endif
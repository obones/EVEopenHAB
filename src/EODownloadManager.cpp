/*
@file    EODownloadManager.cpp
@brief   Contains the download manager definitions
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

//#include <esp32HTTPrequest.h>
#include <EVE.h>

#include "EODownloadManager.h"
#include "EOSettings.h"

namespace EVEopenHAB 
{

    void downloadTask(void * managerPtr)
    {
        DownloadManager& manager = *(reinterpret_cast<DownloadManager*>(managerPtr));

        while (true)
        {
            DownloadManager::downloadRecord record = manager.downloadQueue.dequeue();

            esp32HTTPrequest request;

            request.setDebug(true);
            request.setClientBufferSize(1024);
            request.onReadyStateChange(record.Callback, record.Parameter);
            request.open("GET", record.URL.c_str());
            request.send();
        }
    }

    DownloadManager::DownloadManager() 
    {
        xTaskCreate(downloadTask, "dld", 8192, this, 1, nullptr);
    }

    void DownloadManager::Enqueue(String url, readyStateChangeCB callback, void* optParm)
    {
        downloadQueue.enqueue({ .URL = url, .Callback = callback, .Parameter = optParm });
    }

    DownloadManager& DownloadManager::Instance()
    {
        static DownloadManager instance;
        return instance;
    }
}
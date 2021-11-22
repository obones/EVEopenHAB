/*
@file    EOPostManager.cpp
@brief   Contains the post manager definitions
@date    2021-11-22
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

#include <esp32HTTPrequest.h>
#include <EVE.h>

#include "EOPostManager.h"
#include "EOSettings.h"

namespace EVEopenHAB 
{

    void readyStateChange(void* optParm, esp32HTTPrequest* request, int readyState)
    {
        // if the request finished but failed, place it back in the queue
        if (readyState == 4)
        {
            if (request->responseHTTPcode() < 0)
            {
                PostManager::postRecord* record = reinterpret_cast<PostManager::postRecord*>(optParm);
                
                record->Manager->Enqueue(record->URL, record->Value);
            }
        }
    }

    void postTask(void * managerPtr)
    {
        PostManager& manager = *(reinterpret_cast<PostManager*>(managerPtr));

        while (true)
        {
            PostManager::postRecord record = manager.postQueue.dequeue();

            esp32HTTPrequest request;

            request.setDebug(false);
            request.setClientBufferSize(1040);
            request.onReadyStateChange(readyStateChange, &record);
            request.open("POST", record.URL.c_str());
            request.setReqHeader("Content-Type","text/plain");
            request.send(record.Value.c_str());
        }
    }

    PostManager::PostManager() 
    {
        xTaskCreate(postTask, "pst", 4096, this, 1, nullptr);
    }

    void PostManager::Enqueue(String url, String value)
    {
        postQueue.enqueue({ .URL = url, .Value = value, .Manager = this });
    }

    PostManager& PostManager::Instance()
    {
        static PostManager instance;
        return instance;
    }
}
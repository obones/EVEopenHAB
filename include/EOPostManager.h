/*
@file    EOPostManager.h
@brief   Contains the post manager declarations
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
#ifndef EOPOSTMANAGER_H
#define EOPOSTMANAGER_H

#include <Arduino.h>
#include <esp32HTTPrequest.h>

#include "EOSafeQueue.h"

namespace EVEopenHAB 
{
    class PostManager
    {
        private:
            typedef struct
            {
                String URL;
                String Value;
                int Retries;
                PostManager* Manager;
            } postRecord;

            SafeQueue<postRecord> postQueue;

            PostManager();

            friend void postTask(void * managerPtr);
            friend void readyStateChange(void*, esp32HTTPrequest*, int);

            void Enqueue(String url, String value, int retries);
        public:
            void Enqueue(String url, String value);

            static PostManager& Instance();
    };
}

#endif
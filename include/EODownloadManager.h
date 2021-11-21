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
#include <queue>
#include <mutex>
#include <condition_variable>

namespace EVEopenHAB 
{
    //esp32HTTPrequest https://github.com/boblemaire/esp32HTTPrequest
    //https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
    //https://www.codeproject.com/Articles/5295781/Use-Both-Cores-on-an-ESP32-Easy-Synchronization-wi

    class DownloadManager
    {
        private:
            // A threadsafe-queue.
            template <class T>
            class SafeQueue
            {
                public:
                    SafeQueue(void): q(), m(), c() {}
                    ~SafeQueue(void) {}

                    // Add an element to the queue.
                    void enqueue(T t)
                    {
                        std::lock_guard<std::mutex> lock(m);
                        q.push(t);
                        c.notify_one();
                    }

                    // Get the "front"-element.
                    // If the queue is empty, wait till a element is avaiable.
                    T dequeue(void)
                    {
                        std::unique_lock<std::mutex> lock(m);
                        while(q.empty())
                        {
                            // release lock as long as the wait and reaquire it afterwards.
                            c.wait(lock);
                        }
                        T val = q.front();
                        q.pop();
                        return val;
                    }

                private:
                    std::queue<T> q;
                    mutable std::mutex m;
                    std::condition_variable c;
            };

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
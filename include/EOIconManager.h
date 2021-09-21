/*
@file    EOIconManager.h
@brief   Contains the Icon manager declarations
@date    2021-09-17
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
#ifndef EOICONMANAGER_H
#define EOICONMANAGER_H

#include <vector>

namespace EVEopenHAB 
{
    class IconManager
    {
        private:
            enum class BitmapState { Allocated, Initialized, Loaded };

            typedef struct
            {
                const char* name;
                const char* state;
                uint32_t address;
                uint8_t* buffer;
                size_t bufferLength;
                BitmapState bitmapState;
            } iconRecord;
            
            std::vector<iconRecord> records;

            int16_t indexBeingRetrieved = -1;
            void startRetrieval();

            IconManager() {}

            friend void iconRequestReadyStateChange(void*, asyncHTTPrequest*, int);
        public:
            void MainLoop();

            void Reset();

            int8_t GetIconIndex(const char* name, const char* state); // returns the index of the icon matching name and state
            uint32_t GetAddress(int8_t index);
            void BurstIcon(int8_t index, int16_t x, int16_t y);

            static IconManager* Instance();
    };
}

#endif
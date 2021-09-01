/*
@file    EOMoveable.h
@brief   Contains the moveable element declarations
@date    2021-09-01
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
#ifndef EOMOVEABLE_H
#define EOMOVEABLE_H

#include <Arduino.h>
#include "EOBase.h"

namespace EVEopenHAB 
{
    class Moveable: public Base
    {
        private:
            int16_t left;
            int16_t top;
            int16_t width;
            int16_t height;
        public:
            Moveable(Base* parent);

            Rect ClientRect();

            int16_t Left();
            int16_t Top();
            int16_t Width();
            int16_t Height();

            void SetLeft(int16_t value);
            void SetTop(int16_t value);
            void SetWidth(int16_t value);
            void SetHeight(int16_t value);
    };
}

#endif

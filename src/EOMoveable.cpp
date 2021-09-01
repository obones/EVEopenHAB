/*
@file    EOMoveable.cpp
@brief   Contains the Moveable object definitions
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

#include <EVE.h>
#include "EOMoveable.h"

namespace EVEopenHAB 
{
    Moveable::Moveable(Base* parent): Base(parent)
    {

    }

    Rect Moveable::ClientRect()
    {
        return { .Left = left, .Top = top, .Width = width, .Height = height };
    }

    int16_t Moveable::Left() 
    { 
        return left; 
    }

    int16_t Moveable::Top()
    { 
        return top; 
    }

    int16_t Moveable::Width()
    { 
        return width; 
    }

    int16_t Moveable::Height()
    { 
        return height; 
    }

    void Moveable::SetLeft(int16_t value)
    {
        left = value;
    }

    void Moveable::SetTop(int16_t value)
    {
        top = value;
    }

    void Moveable::SetWidth(int16_t value)
    {
        width = value;
    }

    void Moveable::SetHeight(int16_t value)
    {
        height = value;
    }
}
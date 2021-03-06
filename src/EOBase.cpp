/*
@file    EOBase.cpp
@brief   Contains the Base object definitions
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
#include "EOBase.h"

namespace EVEopenHAB 
{
    Base::Base(Base* parent)
    {
        this->parent = parent;
    }

    uint32_t Base::ClientToScreen2F(int16_t x, int16_t y)
    {
        Point point = ClientToScreen(x, y);
        return VERTEX2F(point.X, point.Y);
    }

    Point Base::ClientToScreen(int16_t x, int16_t y)
    {
        Rect clientRect = ClientRect();

        x += clientRect.Left;
        y += clientRect.Top;

        if (parent != nullptr) 
            return parent->ClientToScreen(x, y);
        else
            return { .X = x, .Y = y };
    }

    Base* Base::Parent()
    {
        return parent;
    }

    void Base::SetDirty()
    {
        if (parent != nullptr)
            parent->SetDirty();
    }

}
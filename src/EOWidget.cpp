/*
@file    EOWidget.cpp
@brief   Contains the sitemap Widget definitions
@date    2021-08-27
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

#include "EOWidget.h"
#include "EOConstants.h"

namespace EVEopenHAB 
{
    Widget::Widget(Base* parent, JsonObject sourceObject): Moveable(parent), linkedItem(sourceObject["item"].as<JsonObject>())
    {
        if (!EnumString<WidgetType>::To(type, sourceObject["type"].as<const char*>()))
            type = WidgetType::Unknown;
        label = sourceObject["label"].as<String>();
        icon = sourceObject["icon"].as<String>();
        visibility = sourceObject["visibility"].as<bool>();
    }

    Widget::~Widget()
    {

    }

    void Widget::Render()
    {
        Point textPoint = ClientToScreen(0, Height() / 2);
        Point topLeft = ClientToScreen(0, 0);
        Point bottomRight = ClientToScreen(Width(), Height());

        EVE_cmd_dl_burst(COLOR_RGB(0xFF, 0,0));
        EVE_cmd_dl_burst(DL_BEGIN | EVE_RECTS);
    	EVE_cmd_dl_burst(LINE_WIDTH(1 * 16)); // size is in 1/16 pixel for this command, regardless of format
        EVE_cmd_dl_burst(VERTEX2F(topLeft.X, topLeft.Y));
        EVE_cmd_dl_burst(VERTEX2F(bottomRight.X, bottomRight.Y));
        EVE_cmd_dl_burst(DL_END);

        EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
        EVE_cmd_text_burst(textPoint.X, textPoint.Y, 28, EVE_OPT_CENTERY, label.c_str());
    }

    WidgetType Widget::Type()
    {
        return type;
    }

    String Widget::Label()
    {
        return label;
    }

    String Widget::Icon()
    {
        return icon;
    }

    bool Widget::Visibility()
    {
        return visibility;
    }

    Item Widget::LinkedItem()
    {
        return linkedItem;
    }
}
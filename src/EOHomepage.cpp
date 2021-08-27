/*
@file    EOHomepage.cpp
@brief   Contains the sitemap Homepage definitions
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

#include "EOHomepage.h"

namespace EVEopenHAB 
{
    Homepage::Homepage(JsonObject sourceObject)
    {
        id = sourceObject["id"].as<String>();

        auto jsonWidgets = sourceObject["widgets"].as<JsonArray>();
        widgets.reserve(jsonWidgets.size());
        for (JsonArray::iterator it = jsonWidgets.begin(); it != jsonWidgets.end(); ++it)//(int widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++)
            widgets.push_back(Widget(it->as<JsonObject>()));
    }

    String Homepage::Id()
    {
        return id;
    }

    std::vector<Widget> Homepage::Widgets()
    {
        return widgets;
    }
}
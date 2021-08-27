/*
@file    EOWidget.h
@brief   Contains the sitemap Widget declarations
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
#ifndef EOWIDGET_H
#define EOWIDGET_H

#include <ArduinoJson.h>
#include <WString.h>
#include "EnumString.h"
#include "EOItem.h"

namespace EVEopenHAB 
{
    enum class WidgetType {
        /*Chart,
        Colorpicker,
        Default,
        Frame,
        Group,
        Image,
        Mapview,
        Selection,
        Setpoint,*/
        Slider,
        Switch,
        Text,
        /*Video,
        Webview,*/
        Unknown
    };
    
    class Widget 
    {
        private:
            WidgetType type;
            String label;
            String icon;
            bool visibility;
            Item linkedItem;

        public:
            Widget(JsonObject sourceObject);

            WidgetType Type();
            String Label();
            String Icon();
            bool Visibility();
            Item LinkedItem();
    };
}

Begin_Enum_String(EVEopenHAB::WidgetType)
{
    /*Enum_String(EVEopenHAB::WidgetType::Chart);
    Enum_String(EVEopenHAB::WidgetType::Colorpicker);
    Enum_String(EVEopenHAB::WidgetType::Default);
    Enum_String(EVEopenHAB::WidgetType::Frame);
    Enum_String(EVEopenHAB::WidgetType::Group);
    Enum_String(EVEopenHAB::WidgetType::Image);
    Enum_String(EVEopenHAB::WidgetType::Mapview);
    Enum_String(EVEopenHAB::WidgetType::Selection);
    Enum_String(EVEopenHAB::WidgetType::Setpoint);*/
    Enum_String(EVEopenHAB::WidgetType::Slider);
    Enum_String(EVEopenHAB::WidgetType::Switch);
    Enum_String(EVEopenHAB::WidgetType::Text);
    /*Enum_String(EVEopenHAB::WidgetType::Video);
    Enum_String(EVEopenHAB::WidgetType::Webview);*/
    Enum_String(EVEopenHAB::WidgetType::Unknown);
}
End_Enum_String;    


#endif
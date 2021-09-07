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
#include "EOBase.h"
#include "EOMoveable.h"
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
    
    class Widget: public Moveable 
    {
        private:
            WidgetType type;
            String label;
            const char* state = NULL;
            String icon;
            bool visibility;
            Item linkedItem;

            void sendCommand(uint8_t tag, uint16_t trackedValue, void* customData);
            void sendSliderValue(uint8_t tag, uint16_t trackedValue, void* customData);
        public:
            Widget(Base* parent, JsonObject sourceObject);
            virtual ~Widget();

            void Render();

            WidgetType Type();
            String Label();
            String Icon();
            bool Visibility();
            Item LinkedItem();
    };
}

Begin_Enum_String(EVEopenHAB::WidgetType)
{
    /*RegisterEnumerator(EVEopenHAB::WidgetType::Chart, "Chart");
    RegisterEnumerator(EVEopenHAB::WidgetType::Colorpicker, "Colorpicker);
    RegisterEnumerator(EVEopenHAB::WidgetType::Default, "Default");
    RegisterEnumerator(EVEopenHAB::WidgetType::Frame, "Frame");
    RegisterEnumerator(EVEopenHAB::WidgetType::Group, "Group");
    RegisterEnumerator(EVEopenHAB::WidgetType::Image, "Image");
    RegisterEnumerator(EVEopenHAB::WidgetType::Mapview, "Mapview");
    RegisterEnumerator(EVEopenHAB::WidgetType::Selection, "Selection");
    RegisterEnumerator(EVEopenHAB::WidgetType::Setpoint, "Setpoint");*/
    RegisterEnumerator(EVEopenHAB::WidgetType::Slider, "Slider");
    RegisterEnumerator(EVEopenHAB::WidgetType::Switch, "Switch");
    RegisterEnumerator(EVEopenHAB::WidgetType::Text, "Text");
    /*RegisterEnumerator(EVEopenHAB::WidgetType::Video, "Video");
    RegisterEnumerator(EVEopenHAB::WidgetType::Webview, "Webview");*/
    RegisterEnumerator(EVEopenHAB::WidgetType::Unknown, "Unknown");
}
End_Enum_String;    


#endif
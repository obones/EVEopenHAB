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

#include <cmath>
#include <EVE.h>

#include "EOWidget.h"
#include "EOConstants.h"
#include "EOItem.h"
#include "EOTagManager.h"

#define OHAB_CMD_UP 0
#define OHAB_CMD_DOWN 1
#define OHAB_CMD_STOP 2

namespace EVEopenHAB 
{
    Widget::Widget(Base* parent, JsonObject sourceObject): Moveable(parent), linkedItem(sourceObject["item"].as<JsonObject>())
    {
        if (!EnumString<WidgetType>::To(type, sourceObject["type"].as<const char*>()))
            type = WidgetType::Unknown;
        label = sourceObject["label"].as<String>();
        icon = sourceObject["icon"].as<String>();
        visibility = sourceObject["visibility"].as<bool>();

        auto openingBracketIndex = label.indexOf('[');
        if (openingBracketIndex >= 0)
        {
            auto closingBracketIndex = label.indexOf(']', openingBracketIndex);
            if (closingBracketIndex > openingBracketIndex)
            {
                // Only store a pointer and place 0 character at appropriate places to save RAM
                state = label.c_str() + openingBracketIndex + 1;
                label[openingBracketIndex] = 0;
                label[closingBracketIndex] = 0;
            }
        }
    }

    Widget::~Widget()
    {

    }

    void Widget::Render()
    {
        Point textPoint = ClientToScreen(0, Height() / 2);
        Point topLeft = ClientToScreen(0, 0);
        Point bottomRight = ClientToScreen(Width(), Height());

        const int16_t rectanglePenWidth = 2;
        const int16_t fontIndex = 28;

        EVE_cmd_dl_burst(COLOR_RGB(0xEE, 0xEE,0xEE));
        EVE_cmd_dl_burst(DL_BEGIN | EVE_RECTS);
    	EVE_cmd_dl_burst(LINE_WIDTH(5 * 16)); // size is in 1/16 pixel for this command, regardless of format
        EVE_cmd_dl_burst(VERTEX2F(topLeft.X, topLeft.Y));
        EVE_cmd_dl_burst(VERTEX2F(bottomRight.X, bottomRight.Y));
        EVE_cmd_dl_burst(DL_COLOR_RGB | WHITE);
        EVE_cmd_dl_burst(VERTEX2F(topLeft.X + rectanglePenWidth, topLeft.Y + rectanglePenWidth));
        EVE_cmd_dl_burst(VERTEX2F(bottomRight.X - rectanglePenWidth, bottomRight.Y - rectanglePenWidth));
    	EVE_cmd_dl_burst(LINE_WIDTH(1 * 16)); // size is in 1/16 pixel for this command, regardless of format
        EVE_cmd_dl_burst(DL_END);

        EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
        EVE_cmd_text_burst(textPoint.X, textPoint.Y, fontIndex, EVE_OPT_CENTERY, label.c_str());

        switch (type)
        {
            case WidgetType::Text:
                if (state)
                {
                    const int16_t textRightMargin = 5 + rectanglePenWidth;

                    textPoint = ClientToScreen(Width() - textRightMargin, Height() / 2);
                    EVE_cmd_text_burst(textPoint.X, textPoint.Y, fontIndex, EVE_OPT_CENTERY | EVE_OPT_RIGHTX, state);
                }
                break;
            
            case WidgetType::Slider:
            {
                float state = linkedItem.State().AsNumber();
                int16_t intState = (std::isnan(state)) ? 0 : round(state);

                const int16_t sliderWidth = Width() / 3;
                const int16_t sliderHeight = 10;
                const int16_t sliderRightMargin = 5 + sliderHeight; // the height is used to draw the button

                Point sliderPoint = ClientToScreen(Width() - sliderWidth - sliderRightMargin, (Height() - sliderHeight) / 2);

                uint8_t tag = TagManager::Instance()->GetNextTag(this, &EVEopenHAB::Widget::sendSliderValue, nullptr);

                EVE_cmd_track(sliderPoint.X, sliderPoint.Y, sliderWidth, sliderHeight, tag);

                EVE_cmd_dl_burst(TAG(tag));
                EVE_cmd_dl_burst(COLOR_RGB(255, 170, 0));
                EVE_cmd_fgcolor_burst(0x999999);
                EVE_cmd_bgcolor_burst(0xDDDDDD);
                EVE_cmd_slider_burst(sliderPoint.X, sliderPoint.Y, sliderWidth, sliderHeight, EVE_OPT_FLAT, intState, 100);

                break;
            }
            case WidgetType::Switch:
                switch (linkedItem.Type())
                {
                    case ItemType::Rollershutter:
                    {
                        const int16_t buttonSize = Height() / 2;
                        const int16_t buttonRightMargin = 5;

                        EVE_cmd_fgcolor_burst(0xDDDDDD);
                        Point buttonPoint = ClientToScreen(Width() - buttonSize - buttonRightMargin, (Height() - buttonSize) / 2);

                        EVE_cmd_dl_burst(TAG(TagManager::Instance()->GetNextTag(this, &EVEopenHAB::Widget::sendCommand, reinterpret_cast<void*>(OHAB_CMD_UP))));
                        EVE_cmd_dl_burst(CMD_LOADIDENTITY);
                        EVE_cmd_translate_burst(0, 3 * 65536 + 5);
                        EVE_cmd_dl_burst(CMD_SETMATRIX);
                        EVE_cmd_button_burst(buttonPoint.X, buttonPoint.Y, buttonSize, buttonSize, fontIndex, EVE_OPT_FLAT, "^");

                        buttonPoint.X -= buttonSize + buttonRightMargin;
                        EVE_cmd_dl_burst(TAG(TagManager::Instance()->GetNextTag(this, &EVEopenHAB::Widget::sendCommand, reinterpret_cast<void*>(OHAB_CMD_STOP))));
                        EVE_cmd_dl_burst(CMD_LOADIDENTITY);
                        EVE_cmd_dl_burst(CMD_SETMATRIX);
                        EVE_cmd_button_burst(buttonPoint.X, buttonPoint.Y, buttonSize, buttonSize, fontIndex - 1, EVE_OPT_FLAT, "X");

                        buttonPoint.X -= buttonSize + buttonRightMargin;
                        EVE_cmd_dl_burst(TAG(TagManager::Instance()->GetNextTag(this, &EVEopenHAB::Widget::sendCommand, reinterpret_cast<void*>(OHAB_CMD_DOWN))));
                        EVE_cmd_dl_burst(CMD_LOADIDENTITY);
                        EVE_cmd_rotatearound_burst(4, 10, 32768, 65536);
                        EVE_cmd_dl_burst(CMD_SETMATRIX);
                        EVE_cmd_button_burst(buttonPoint.X, buttonPoint.Y, buttonSize, buttonSize, fontIndex, EVE_OPT_FLAT, "^");
                        EVE_cmd_dl_burst(CMD_LOADIDENTITY);
                        EVE_cmd_dl_burst(CMD_SETMATRIX);

                        EVE_cmd_dl_burst(TAG(0));

                        break;
                    }
                    case ItemType::Number:
                        break;

                    case ItemType::None:
                    case ItemType::Unsupported:
                        break;
                }

                break;
            
            case WidgetType::Unknown:
                break;
        }
    }

    void Widget::sendCommand(uint8_t tag, uint16_t trackedValue, void* customData)
    {
        Serial.print("Widget ");
        Serial.print(label);
        Serial.print(" received tag ");
        Serial.print(tag);
        Serial.print(" - tracked value = ");
        Serial.print(trackedValue);
        Serial.print(" - customData = ");
        Serial.printf("%p", customData);
        Serial.println("");
    }

    void Widget::sendSliderValue(uint8_t tag, uint16_t trackedValue, void* customData)
    {
        Serial.print("Widget ");
        Serial.print(label);
        Serial.print(" received tracked tag ");
        Serial.print(tag);
        Serial.print(" - tracked value = ");
        Serial.print(trackedValue);
        Serial.print(" - customData = ");
        Serial.printf("%p", customData);
        Serial.println("");
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
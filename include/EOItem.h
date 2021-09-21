/*
@file    EOItem.h
@brief   Contains the sitemap Item declarations
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
#ifndef EOITEM_H
#define EOITEM_H

#include <ArduinoJson.h>
#include <WString.h>
#include "EnumString.h"
#include "EOParsedState.h"

namespace EVEopenHAB 
{
    enum class ItemType {
        None,
        /*Color,
        Contact,
        DateTime,
        Dimmer,
        Group,
        Image,
        Location,*/
        Number,
        /*NumberWithDimension,
        Player,*/
        Rollershutter,
        /*StringItem,
        Switch*/
        Unsupported
    };

    class Item
    {
        private:
            ItemType type;
            String link;
            ParsedState state;
        public:
            Item(JsonObject sourceObject);
        
            ItemType Type() const;
            const String& Link() const;
            const ParsedState& State() const;

            void SetState(const char* strValue);
    };
}

Begin_Enum_String(EVEopenHAB::ItemType)
{
    RegisterEnumerator(EVEopenHAB::ItemType::None, "None");
    /*RegisterEnumerator(EVEopenHAB::ItemType::Color, "Color");
    RegisterEnumerator(EVEopenHAB::ItemType::Contact, "Contact");
    RegisterEnumerator(EVEopenHAB::ItemType::DateTime, "DateTime");
    RegisterEnumerator(EVEopenHAB::ItemType::Dimmer, "Dimmer");
    RegisterEnumerator(EVEopenHAB::ItemType::Group, "Group");
    RegisterEnumerator(EVEopenHAB::ItemType::Image, "Image");
    RegisterEnumerator(EVEopenHAB::ItemType::Location, "Location");*/
    RegisterEnumerator(EVEopenHAB::ItemType::Number, "Number");
    /*RegisterEnumerator(EVEopenHAB::ItemType::NumberWithDimension, "NumberWithDimension");
    RegisterEnumerator(EVEopenHAB::ItemType::Player, "Player");*/
    RegisterEnumerator(EVEopenHAB::ItemType::Rollershutter, "Rollershutter");
    /*RegisterEnumerator(EVEopenHAB::ItemType::StringItem, "StringItem");
    RegisterEnumerator(EVEopenHAB::ItemType::Switch, "Switch");*/
    RegisterEnumerator(EVEopenHAB::ItemType::Unsupported, "Unsupported");
}
End_Enum_String;    

#endif

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
        public:
            Item(JsonObject sourceObject);
        
            ItemType Type();
    };
}

Begin_Enum_String(EVEopenHAB::ItemType)
{
    Enum_String(EVEopenHAB::ItemType::None);
    /*Enum_String(EVEopenHAB::ItemType::Color);
    Enum_String(EVEopenHAB::ItemType::Contact);
    Enum_String(EVEopenHAB::ItemType::DateTime);
    Enum_String(EVEopenHAB::ItemType::Dimmer);
    Enum_String(EVEopenHAB::ItemType::Group);
    Enum_String(EVEopenHAB::ItemType::Image);
    Enum_String(EVEopenHAB::ItemType::Location);*/
    Enum_String(EVEopenHAB::ItemType::Number);
    /*Enum_String(EVEopenHAB::ItemType::NumberWithDimension);
    Enum_String(EVEopenHAB::ItemType::Player);*/
    Enum_String(EVEopenHAB::ItemType::Rollershutter);
    /*Enum_String(EVEopenHAB::ItemType::StringItem);
    Enum_String(EVEopenHAB::ItemType::Switch);*/
    Enum_String(EVEopenHAB::ItemType::Unsupported);
}
End_Enum_String;    

#endif

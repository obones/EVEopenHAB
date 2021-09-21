/*
@file    EOParsedState.cpp
@brief   Contains the ParsedState definitions
@date    2021-09-07
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

#include <Arduino.h>
#include <limits>

#include "EOParsedState.h"

namespace EVEopenHAB 
{
    ParsedState::ParsedState(const String& sourceValue)
    {
        asString = sourceValue;

        asBoolean = parseBoolean(asString);
        asNumber = parseNumber(asString);
    }

    const String& ParsedState::AsString() const
    {
        return asString;
    }
    
    bool ParsedState::AsBoolean() const
    {
        return asBoolean;
    }

    float ParsedState::AsNumber() const
    {
        return asNumber;
    }

    bool ParsedState::parseBoolean(const String& sourceValue)
    {
        if (sourceValue == "ON")
            return true;

        const char* sourcePtr = sourceValue.c_str();
        char* endPtr = NULL;
        long convertedValue = strtol(sourcePtr, &endPtr, 10);
        if (endPtr != sourcePtr)
            return convertedValue > 0;

        return false;
    }

    float ParsedState::parseNumber(const String& sourceValue)
    {
        if (sourceValue == "ON")
            return 100.0;
        if (sourceValue == "OFF")
            return 0.0;

        const char* sourcePtr = sourceValue.c_str();
        char* endPtr = NULL;
        float convertedValue = strtof(sourcePtr, &endPtr);
        if (endPtr != sourcePtr)
            return convertedValue;

        return std::numeric_limits<float>::quiet_NaN();
    }
}
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

#include <EVE.h>
#include "EOHomepage.h"
#include "EOConstants.h"
#include "EOTagManager.h"

namespace EVEopenHAB 
{
    const int16_t TopMargin = 40;

    Homepage::Homepage(JsonObject sourceObject): Base(nullptr)
    {
        id = sourceObject["id"].as<String>();

        auto jsonWidgets = sourceObject["widgets"].as<JsonArray>();
        widgets.reserve(jsonWidgets.size());
        for (JsonArray::iterator it = jsonWidgets.begin(); it != jsonWidgets.end(); ++it)//(int widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++)
            widgets.push_back(new Widget(this, it->as<JsonObject>()));
    }

    Homepage::~Homepage()
    {
        for (int widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++)
            delete widgets[widgetIndex];
        widgets.clear();
    }

    Rect Homepage::ClientRect()
    {
        return {.Left = 0, .Top = TopMargin, .Width = EVE_HSIZE, .Height = EVE_VSIZE - TopMargin};
    }

    void Homepage::LayoutChildren()
    {
        const int16_t margin = 20;
        
        int16_t widgetWidth = EVE_HSIZE / 2 - 2 * margin;
        int16_t widgetHeight = 80;
        int16_t widgetTop = margin;

        for (int widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++)
        {
            int16_t widgetLeft = (widgetIndex % 2 == 0) ? margin : EVE_HSIZE / 2 + margin;

            auto currentWidget = widgets[widgetIndex];

            currentWidget->SetLeft(widgetLeft);
            currentWidget->SetTop(widgetTop);
            currentWidget->SetWidth(widgetWidth);
            currentWidget->SetHeight(widgetHeight);

            if (widgetIndex % 2 == 1)
                widgetTop += widgetHeight + margin;
        }
    }

    void Homepage::Render()
    {
        TagManager::Instance()->Reset();

        isDirty = false;

        EVE_start_cmd_burst();
        EVE_cmd_dl_burst(CMD_DLSTART); // Start the display list 
        EVE_cmd_dl_burst(TAG(0)); // By default, do not use the following objects for touch-detection 
    	EVE_cmd_dl_burst(VERTEX_FORMAT(0)); // reduce precision for VERTEX2F to 1 pixel instead of 1/16 pixel default 

        EVE_cmd_dl_burst(DL_CLEAR_RGB | WHITE);
        EVE_cmd_dl_burst(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);

        // Black text
        EVE_cmd_dl_burst(DL_COLOR_RGB | BLACK);
        EVE_cmd_text_burst(EVE_HSIZE/2, 15, 29, EVE_OPT_CENTERX, "EVEopenHAB");

        for (int widgetIndex = 0; widgetIndex < widgets.size(); widgetIndex++)
        {
            EVE_cmd_dl_burst(SAVE_CONTEXT());
            widgets[widgetIndex]->Render();
            EVE_cmd_dl_burst(RESTORE_CONTEXT());
        }

        EVE_cmd_dl_burst(DL_DISPLAY); // put in the display list to mark its end
        EVE_cmd_dl_burst(CMD_SWAP); // tell EVE to use the new display list
        
        EVE_end_cmd_burst();
        
        Serial.println("    Second busy loop");
        while (EVE_busy());    
    }

    String Homepage::Id()
    {
        return id;
    }

    std::vector<Widget*> Homepage::Widgets()
    {
        return widgets;
    }

    void Homepage::SetDirty()
    {
        isDirty = true;
    }

    bool Homepage::IsDirty()
    {
        return isDirty;
    }

}

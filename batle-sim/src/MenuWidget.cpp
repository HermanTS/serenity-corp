/*
 * MenuWidget.cpp
 *
 *  Created on: 21 февр. 2020 г.
 *      Author: gstsvetkov
 */

#include "MenuWidget.h"

#include <iostream>
#include <chrono>
#include <iomanip>

MenuWidget::MenuWidget(int x, int y):enemyNameMaxLen(128)
{
    this->hight = 400;
    this->widght = 200;
    this->x_pos = x;
    this->y_pos = y;
    this->flags = NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR;

    enemyName = new char[enemyNameMaxLen];
    memset(enemyName, 0, enemyNameMaxLen);

}

MenuWidget::~MenuWidget()
{
// TODO Auto-generated destructor stub
}

void MenuWidget::CustomDraw(struct nkc* nkcHandle)
{
    struct nk_command_buffer *canvas =  nk_window_get_canvas(context);
    struct nk_rect fieldBounds = nk_window_get_content_region(context);

    nk_layout_row_dynamic(context, 25, 1);
    nk_label(context, "Prepare to the battle", NK_TEXT_LEFT);

    nk_label(context, "Our Forces", NK_TEXT_LEFT);
    static int selected_item = 0;
    static const char *items[] = {"Item 0","item 1","item 2"};
    nk_layout_row_dynamic(context, 25, 2);
    if (nk_combo_begin_label(context, items[selected_item], nk_vec2(nk_widget_width(context), 200))) {
        nk_layout_row_dynamic(context, 35, 1);
        for (int i = 0; i < 3; ++i)
            if (nk_combo_item_label(context, items[i], NK_TEXT_LEFT))
                selected_item = i;
        nk_combo_end(context);
    }

    if (nk_button_label(context, "Add"))
    {
        std::cout << "Selected unit is - \"" << selected_item << "\"" << std::endl;
    }

    static int enemyNameLen;
    nk_layout_row_dynamic(context, 25, 2);
    nk_label(context, "Enemy name:", NK_TEXT_LEFT);
    nk_edit_string(context, NK_EDIT_SIMPLE, enemyName, &enemyNameLen, enemyNameMaxLen, nk_filter_default);
    if (nk_button_label(context, "Add") && enemyNameLen)
    {
        auto  time = std::time(nullptr);
        std::cout <<  std::put_time( std::gmtime(&time), "%F %T") << " Locate enemy - \"" << enemyName << "\" " << std::endl;
        memset(enemyName, 0, enemyNameMaxLen);
        enemyNameLen = 0;
    }

    nk_layout_row_dynamic(context, 25, 1);
    if (nk_button_label(context, "Start battle"))
    {
        auto  time = std::time(nullptr);
        std::cout << std::put_time( std::gmtime(&time), "%F %T") << " Battle started" << std::endl;
    }

    if (nk_button_label(context, "End battle"))
    {
        auto  time = std::time(nullptr);
        std::cout << std::put_time( std::gmtime(&time), "%F %T") << " Battle ended" << std::endl;
    }

}

/*
 * BattleField.cpp
 *
 *  Created on: 17 февр. 2020 г.
 *      Author: gstsvetkov
 */

#include "BattleField.h"

BattleField::BattleField(std::string name, unsigned int x, unsigned int y): TeamName(name), scale(10)
{
    this->title = TeamName.c_str();
    this->hight = 400;
    this->widght = 400;
    this->x_pos = x;
    this->y_pos = y;
    this->flags = NK_WINDOW_BORDER|NK_WINDOW_CLOSABLE|NK_WINDOW_NO_SCROLLBAR;

    for(int i = 0; i < scale; i++)
    {
        std::list<cell> row(scale);
        battleMap.push_back(row);
    }

    cellColor[CELL_STATE_EMPTY] = nk_rgb(40,40,40);
    cellColor[CELL_STATE_BUSY] = nk_rgb(40,200,40);
    cellColor[CELL_STATE_SHOT] = nk_rgb(200,40,40);
    cellColor[CELL_STATE_MISS] = nk_rgb(200,200,200);

}

BattleField::~BattleField()
{
// TODO Auto-generated destructor stub
}

void BattleField::CustomDraw(nkc * nkcHandle)
{

    struct nk_command_buffer *canvas =  nk_window_get_canvas(context);
    struct nk_rect fieldBounds = nk_window_get_content_region(context);

    //set start points
    for (auto collum = battleMap.begin(); collum != battleMap.end(); ++collum)
    {
        for (auto ItCell = collum->begin(); ItCell != collum->end(); ++ItCell)
        {
            ItCell->rec.h = fieldBounds.h/scale;
            ItCell->rec.w = fieldBounds.w/scale;
        }

        collum->begin()->rec.x = fieldBounds.x;
        collum->begin()->rec.y = fieldBounds.y + std::distance(battleMap.begin(), collum)*collum->begin()->rec.h;

    }

    for (auto collum = battleMap.begin(); collum != battleMap.end(); ++collum)
    {
        for (auto ItCell = collum->begin(); ItCell != collum->end(); ++ItCell)
        {

            ItCell->rec.x = collum->begin()->rec.x + std::distance(collum->begin(), ItCell)*ItCell->rec.w;
            ItCell->rec.y = collum->begin()->rec.y;

            nk_stroke_rect(canvas, ItCell->rec, 1, 1, nk_rgb(0,0,0));
            nk_fill_rect(canvas, ItCell->rec,0, cellColor[ItCell->state]);

            if (nk_input_is_mouse_hovering_rect(&context->input, ItCell->rec))
            {
//                        nk_tooltip(context, name.c_str());
            }
        }
    }

}

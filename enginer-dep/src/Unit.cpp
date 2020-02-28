/*
 * Unit.cpp
 *
 *  Created on: 5 янв. 2020 г.
 *      Author: Геман
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include "Unit.h"

namespace ship
{

using namespace std;

Unit::Unit ():name("default_unit"), state(STATE_GOOD), lastState(STATE_MAX),
RESOURCES_DIR("resources/"), IMAGE_FNAME_DEFAULT("default_unit"), IMAGE_FNAME_GOOD("_good.gif"),
IMAGE_FNAME_BAD("_bad.gif"), IMAGE_FNAME_WARN("_warn.gif")
{
    title = name.c_str();
    mtxState = new std::mutex();

    cout << "Initiate unit " << name << endl;
}

Unit::Unit (string name,  int x, int y, int w, int h):
        name(name), state(STATE_GOOD), lastState(STATE_MAX),
RESOURCES_DIR("resources/"), IMAGE_FNAME_DEFAULT("default_unit"), IMAGE_FNAME_GOOD("_good.gif"),
IMAGE_FNAME_BAD("_bad.gif"), IMAGE_FNAME_WARN("_warn.gif")
{
    this->title = name.c_str();
    this->x_pos= x;
    this->y_pos =y;
    this->widght = w;
    this->hight = h;
    this->flags = NK_WINDOW_BACKGROUND|NK_WINDOW_NO_SCROLLBAR;

    mtxState = new std::mutex();

    cout << "Initiate unit " << name << endl;
}

Unit::~Unit()
{
    nkc_image_free(&imageGood);
    nkc_image_free(&imageWarn);
    nkc_image_free(&imageBad);
}

//std::mutex mtxState;
uint32_t Unit::getState (void)
{
    lock_guard<std::mutex> lk(*mtxState);
    return state;
}

void Unit::setState(state_t newState)
{
    lock_guard<std::mutex> lk(*mtxState);
    if (state != newState)
    {
        lastState = state;
        state = newState;
    }
}

string Unit::getName (void)
{
    return name;
}

void Unit::CustomDraw(struct nkc* nkcHandle)
{
    if (getState() != lastState)
    {
        struct nk_image* image;
        switch (getState())
        {
            case STATE_GOOD:
                image = &imageGood;
                break;
            case STATE_WARN:
                image = &imageWarn;
                break;
            case STATE_BAD:
                image = &imageBad;
                break;
            default:
                return;
        }

        if (!image->handle.ptr)
            getImages(nkcHandle);

        struct nk_command_buffer *canvas;
        canvas = nk_window_get_canvas(context);
        nk_image(context, *image);
        struct nk_rect img_rec = nk_window_get_content_region(context);

        nk_draw_image(canvas, img_rec, image, nk_rgb(0,0,0));

        if (nk_input_is_mouse_hovering_rect(&context->input, img_rec))
            nk_tooltip(context, name.c_str());

    }
}

void Unit::getImages(struct nkc* nkcHandle)
{
    for (uint8_t i = 0; i < STATE_MAX; i++)
    {
        string fname;
        switch (i)
        {
            case STATE_GOOD:
                fname = RESOURCES_DIR + name + IMAGE_FNAME_GOOD;
                break;
            case STATE_WARN:
                fname = RESOURCES_DIR + name + IMAGE_FNAME_WARN;
                break;
            case STATE_BAD:
                fname = RESOURCES_DIR + name + IMAGE_FNAME_BAD;
                break;
            default:
                return;
        }

        if (!nkc_file_exists(fname.c_str()))
            fname.replace(RESOURCES_DIR.length(), name.length(), IMAGE_FNAME_DEFAULT);

        switch (i)
        {
            case STATE_GOOD:
                imageGood = nkc_load_image_file(nkcHandle, fname.c_str());
                break;
            case STATE_WARN:
                imageWarn = nkc_load_image_file(nkcHandle, fname.c_str());
                break;
            case STATE_BAD:
                imageBad = nkc_load_image_file(nkcHandle, fname.c_str());
                break;
            default:
                return;
        }
    }
}

} /* namespace ship */

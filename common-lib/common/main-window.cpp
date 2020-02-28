/*
 * main-window.c
 *
 *  Created on: 27 dec, 2019 y.
 *      Author: gstsvetkov
 */

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <list>
#include <thread>
#include "nuklear_cross.h"

#include "main-window.h"
#include "window-widget.h"

MainWindow::MainWindow(void):  context(nullptr), title("Engeneer department"),
                        hight(320),widht(640),window_mode(NKC_WIN_NORMAL)
{
    ListWidgets = new list <WindowWidget*>;
}

MainWindow::MainWindow(list <WindowWidget*>* ListWidgets , uint32_t hight, uint32_t widht, enum nkc_window_mode mode ):
                        context(NULL), title("Engeneer department"),
                        hight(hight),widht(widht), window_mode(mode), ListWidgets(ListWidgets)
{
}

void MainWindow::start(void)
{

    nkcHandle.keepRunning = nk_true;
}

void MainWindow::stop(void)
{
    nkcHandle.keepRunning = nk_false;
}

void MainWindow::execute(void)
{
    if (context == nullptr)
        context = nkc_init( &nkcHandle, title, widht, hight, window_mode);

    while (nkcHandle.keepRunning && (context != nullptr))
    {
        drawWindow();
        eventHandler();
    }
    nkc_shutdown(&nkcHandle);
}

void MainWindow::drawWindow(void)
{
    /* Nuklear GUI code */
    std::list<WindowWidget*>::iterator ItWidgets;
    for (ItWidgets = ListWidgets->begin(); ItWidgets != ListWidgets->end(); ++ItWidgets)
        (*ItWidgets)->Draw(&nkcHandle);

    struct nk_color background = nk_rgb(40,40,40);
    nkc_render(&nkcHandle, background);
    /* End Nuklear GUI */
}

void MainWindow::eventHandler(void)
{
    union nkc_event e = nkc_poll_events(&nkcHandle);
    switch (e.type){
    case NKC_EWINDOW:
    case NKC_EQUIT:
        stop();
        break;
    case NKC_EKEY:
#ifdef GLOBAL_KEY_EVENT_DEBUG
        std::cout << nkc_get_key_char(e.key.code) << " key pressed" << std::endl;
#endif
        break;
    default:
        break;
    }
}


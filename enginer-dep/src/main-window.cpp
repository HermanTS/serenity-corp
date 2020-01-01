/*
 * main-window.c
 *
 *  Created on: 27 dec, 2019 y.
 *      Author: gstsvetkov
 */

#include <cstdlib>
#include "main-window.h"
#include "nuklear_cross.h"

#include "window-widget.h"

MainWindow::MainWindow(void):  context(NULL), title("Engeneer department"),
                        hight(320),widht(640),window_mode(NKC_WIN_NORMAL)
{
    ListWidgets = new list <WindowWidget*>;
}

MainWindow::MainWindow(list <WindowWidget*>* ListWidgets):  context(NULL), title("Engeneer department"),
                        hight(320),widht(640),window_mode(NKC_WIN_NORMAL), ListWidgets(ListWidgets)
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
    if (context == NULL)
        context = nkc_init( &nkcHandle, title, widht, hight, window_mode);

    while (nkcHandle.keepRunning && (context != NULL))
    {
        drawWindow();
        eventHandler();
    }
    nkc_shutdown(&nkcHandle);
}

void MainWindow::drawWindow(void)
{
    nkc_render_bg(&nkcHandle, nk_rgb(40,40,40) );
    /* Nuklear GUI code */

    std::list<WindowWidget*>::iterator ItWidgets;
    for (ItWidgets = ListWidgets->begin(); ItWidgets != ListWidgets->end(); ++ItWidgets)
        (*ItWidgets)->Draw(context);

    nkc_render_gui(&nkcHandle);
    /* End Nuklear GUI */
}

void MainWindow::eventHandler(void)
{
    union nkc_event e = nkc_poll_events(&nkcHandle);
    if( (e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT) )
        stop();

    if( (e.type == NKC_EKEY) )
    {
        printf("%c key pressed\n", nkc_get_key_char(e.key.code));
    }
}


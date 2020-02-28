/*
 * main-window.h
 *
 *  Created on: 27 ���. 2019 �.
 *      Author: gstsvetkov
 */

#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <list>
#include <iterator>
#include <cstdint>

#include "nuklear_cross.h"
#include "window-widget.h"

using namespace std;

class MainWindow {

public:
    MainWindow(void);
    MainWindow(list <WindowWidget*>* ListWidgets , uint32_t hight, uint32_t widht, enum nkc_window_mode mode );
    void start(void);
    void stop(void);
    void execute(void);
private:
    void drawWindow(void);
    void eventHandler(void);

    struct nkc nkcHandle;
    struct nk_context* context;
    const char* title;
    int hight;
    int widht;
    enum nkc_window_mode window_mode;

    list <WindowWidget*>* ListWidgets;

};


#endif /* MAIN_WINDOW_H_ */

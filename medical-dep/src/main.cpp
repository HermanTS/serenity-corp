/*
 * main.c
 *
 *  Created on: 26 dec. 2019 year.
 *      Author: gstsvetkov
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <thread>

#define NKC_IMPLEMENTATION
#include "nuklear_cross.h"

#include "medical-dep.h"
#include "main-window.h"
#include "NoteWidget.h"

int main(int argc, char **argv) {
    std::cout << "Running " << MY_NAME << " console" << std::endl;
    std::cout <<  MY_NAME << " console ready" << std::endl;
    std::cout <<  MY_NAME << " console start user interface" << std::endl;
    std::list <WindowWidget*> lstWidgets;

    MainWindow Window(&lstWidgets, 768, 640, NKC_WIN_NORMAL);
    Window.start();
    std::thread TWindow(MainWindow::execute, Window);

	NoteWidget DocNotes(MY_NAME);
	lstWidgets.push_back(&DocNotes);

    TWindow.join();
    std::cout << MY_NAME << " console disable" <<std::endl;

	return 0;
}


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

#include "enginer-dep.h"
#include "main-window.h"
#include "Ship.h"

int main(int argc, char **argv) {
    std::cout << "Running " << MY_NAME << " console" << std::endl;
    std::cout <<  MY_NAME << " console ready" << std::endl;
    std::cout <<  MY_NAME << " console start user interface" << std::endl;
    std::list <WindowWidget*> lstWidgets;

    MainWindow Window(&lstWidgets, 320, 640, NKC_WIN_NORMAL);
    Window.start();
    std::thread TWindow(MainWindow::execute, Window);

    ship::Ship Serenity;
    std::thread TSerenity (ship::Ship::execute, &Serenity);
    TSerenity.detach();

    lstWidgets.insert(lstWidgets.end(), Serenity.getUnitsList()->begin(), Serenity.getUnitsList()->end());

    TWindow.join();
    std::cout << MY_NAME << "console disable" <<std::endl;

	return 0;
}


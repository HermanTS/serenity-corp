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

#include "batle-sim.h"
#include "main-window.h"
#include "BattleField.h"
#include "MenuWidget.h"

int main(int argc, char **argv) {
    std::cout << "Running " << MY_NAME << " console" << std::endl;
    std::cout <<  MY_NAME << " console ready" << std::endl;
    std::cout <<  MY_NAME << " console start user interface" << std::endl;
    std::list <WindowWidget*> lstWidgets;

    MainWindow Window(&lstWidgets, 768, 1024, NKC_WIN_NORMAL);
    Window.start();
    std::thread TWindow(MainWindow::execute, Window);

    MenuWidget Menu(10, 10);
    lstWidgets.push_back(&Menu);

    BattleField BFOur("Sirius", 210, 10);
    lstWidgets.push_back(&BFOur);

    BattleField BFEnemy("Enemy", 610, 10);
    lstWidgets.push_back(&BFEnemy);



    TWindow.join();
    std::cout << MY_NAME << " console disable" <<std::endl;

	return 0;
}


/*
 * MenuWidget.h
 *
 *  Created on: 21 февр. 2020 г.
 *      Author: gstsvetkov
 */

#ifndef SRC_MENUWIDGET_H_
#define SRC_MENUWIDGET_H_

#include "window-widget.h"
#include "nuklear_cross.h"

class MenuWidget: public WindowWidget
{
public:
    MenuWidget(int x, int y);
    virtual ~MenuWidget();
private:
    void CustomDraw(struct nkc* nkcHandle);
    char* enemyName;
    int enemyNameMaxLen;
};

#endif /* SRC_MENUWIDGET_H_ */

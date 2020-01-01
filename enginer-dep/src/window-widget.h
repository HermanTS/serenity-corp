/*
 * window-widget.h
 *
 *  Created on: 29 дек. 2019 г.
 *      Author: Геман
 */

#ifndef WINDOW_WIDGET_H_
#define WINDOW_WIDGET_H_

#include "nuklear_cross.h"

using namespace std;

class WindowWidget{
public:
	WindowWidget(void);
	WindowWidget(char* title, int x, int y, int w, int h, nk_flags flags);

	void Draw(nk_context *ctx);
protected:
	virtual void CustomDraw(nk_context *ctx) {return;};

	const char* title;
	int x_pos;
	int y_pos;
	int widght;
	int hight;
	nk_flags flags;
};


class TestWidget:public WindowWidget{
	void CustomDraw(nk_context *ctx);
};



#endif /* WINDOW_WIDGET_H_ */

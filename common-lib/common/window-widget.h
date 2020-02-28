/*
 * window-widget.h
 *
 *  Created on: 29 ���. 2019 �.
 *      Author: �����
 */

#ifndef WINDOW_WIDGET_H_
#define WINDOW_WIDGET_H_

#include "nuklear_cross.h"
#include "stb_image.h"

class WindowWidget{
public:
	WindowWidget(void);
	WindowWidget(char* title);
	WindowWidget(char* title, int x, int y, int w, int h, nk_flags flags);
    virtual ~WindowWidget(void){};
	void Draw(struct nkc* nkcHandle);
protected:
	virtual void CustomDraw(struct nkc* nkcHandle){};

	const char* title;
	int x_pos;
	int y_pos;
	int widght;
	int hight;
	nk_flags flags;
	struct nk_context* context;
};


class TestWidget : public WindowWidget{
	void CustomDraw(struct nkc* nkcHandle);
};



#endif /* WINDOW_WIDGET_H_ */

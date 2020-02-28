/*
 * window-widget.cpp
 *
 *  Created on: 29 ���. 2019 �.
 *      Author: �����
 */
#include "window-widget.h"
#include "nuklear_cross.h"


WindowWidget::WindowWidget(void): title ("Show"), x_pos(0), y_pos(0),
								widght(20), hight(20), flags(NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE),
								context(nullptr)
{}

WindowWidget::WindowWidget(char* title): title (title), x_pos(0), y_pos(0),
                                widght(20), hight(20), flags(NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE),
                                context(nullptr)
{}

WindowWidget::WindowWidget(char* title, int x, int y, int w, int h, nk_flags flags):
		title (title), x_pos(x), y_pos(y), widght(w), hight(h), flags(flags), context(nullptr)
{}

void WindowWidget::Draw(struct nkc* nkcHandle)
{
    if (context == nullptr)
        context = nkc_get_ctx(nkcHandle);

	if (nk_begin(context, title, nk_recti(x_pos, y_pos, widght, hight), flags))
	{
		CustomDraw(nkcHandle);
	}
	nk_end(context);
}

void TestWidget::CustomDraw(struct nkc* nkcHandle)
{
	nk_layout_row_static(context, 30, 80, 1);
	if (nk_button_label(context, "button")) {
		/* event handling */
		printf("Button pressed\n");
	}

	/* fixed widget window ratio width */
	nk_layout_row_dynamic(context, 30, 2);
	if (nk_option_label(context, "easy", 1)) ;
	if (nk_option_label(context, "hard", 0)) ;

	/* custom widget pixel width */
	nk_layout_row_begin(context, NK_STATIC, 30, 2);
	{
		float val = 30;
		nk_layout_row_push(context, 50);
		nk_label(context, "Volume:", NK_TEXT_LEFT);
		nk_layout_row_push(context, 110);
		nk_slider_float(context, 0, &val, 100.0f, 1.0f);
	}
	nk_layout_row_end(context);
}

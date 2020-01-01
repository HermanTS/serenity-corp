/*
 * window-widget.cpp
 *
 *  Created on: 29 дек. 2019 г.
 *      Author: Геман
 */
#include "window-widget.h"
#include "nuklear_cross.h"


WindowWidget::WindowWidget(void): title ("Show"), x_pos(50), y_pos(50),
								widght(220), hight(220), flags(NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)
{}

WindowWidget::WindowWidget(char* title, int x, int y, int w, int h, nk_flags flags):
		title (title), x_pos(x), y_pos(y), widght(w), hight(h), flags(flags)
{}

void WindowWidget::Draw(nk_context *ctx)
{
	if (nk_begin(ctx, title, nk_recti(x_pos, y_pos, widght, hight),
	    		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE))
	{
		CustomDraw(ctx);
	}
	nk_end(ctx);
}

void TestWidget::CustomDraw(nk_context *ctx)
{
	nk_layout_row_static(ctx, 30, 80, 1);
	if (nk_button_label(ctx, "button")) {
		/* event handling */
		printf("Button pressed\n");
	}

	/* fixed widget window ratio width */
	nk_layout_row_dynamic(ctx, 30, 2);
	if (nk_option_label(ctx, "easy", 1)) ;
	if (nk_option_label(ctx, "hard", 0)) ;

	/* custom widget pixel width */
	nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
	{
		float val = 30;
		nk_layout_row_push(ctx, 50);
		nk_label(ctx, "Volume:", NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 110);
		nk_slider_float(ctx, 0, &val, 100.0f, 1.0f);
	}
	nk_layout_row_end(ctx);
}

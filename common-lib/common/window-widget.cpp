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

///** EXAMPLE OF TEXT FIELDS
	static const float ratio[] = {120, 150};
    static char field_buffer[64];
    static char text[9][64];
    static int text_len[9];
    static char box_buffer[512];
    static int field_len;
    static int box_len;
    nk_flags active;

    nk_layout_row(context, NK_STATIC, 25, 2, ratio);
    nk_label(context, "Default:", NK_TEXT_LEFT);

    nk_edit_string(context, NK_EDIT_SIMPLE, text[0], &text_len[0], 64, nk_filter_default);
    nk_label(context, "Int:", NK_TEXT_LEFT);
    nk_edit_string(context, NK_EDIT_SIMPLE, text[1], &text_len[1], 64, nk_filter_decimal);
    nk_label(context, "Float:", NK_TEXT_LEFT);
    nk_edit_string(context, NK_EDIT_SIMPLE, text[2], &text_len[2], 64, nk_filter_float);
    nk_label(context, "Hex:", NK_TEXT_LEFT);
    nk_edit_string(context, NK_EDIT_SIMPLE, text[4], &text_len[4], 64, nk_filter_hex);
    nk_label(context, "Octal:", NK_TEXT_LEFT);
    nk_edit_string(context, NK_EDIT_SIMPLE, text[5], &text_len[5], 64, nk_filter_oct);
    nk_label(context, "Binary:", NK_TEXT_LEFT);
    nk_edit_string(context, NK_EDIT_SIMPLE, text[6], &text_len[6], 64, nk_filter_binary);

    nk_label(context, "Password:", NK_TEXT_LEFT);
    {
        int i = 0;
        int old_len = text_len[8];
        char buffer[64];
        for (i = 0; i < text_len[8]; ++i) buffer[i] = '*';
        nk_edit_string(context, NK_EDIT_FIELD, buffer, &text_len[8], 64, nk_filter_default);
        if (old_len < text_len[8])
            memcpy(&text[8][old_len], &buffer[old_len], (nk_size)(text_len[8] - old_len));
    }

    nk_label(context, "Field:", NK_TEXT_LEFT);
    nk_edit_string(context, NK_EDIT_FIELD, field_buffer, &field_len, 64, nk_filter_default);

    nk_label(context, "Box:", NK_TEXT_LEFT);
    nk_layout_row_static(context, 180, 278, 1);
    nk_edit_string(context, NK_EDIT_BOX, box_buffer, &box_len, 512, nk_filter_default);

    nk_layout_row(context, NK_STATIC, 25, 2, ratio);
    active = nk_edit_string(context, NK_EDIT_FIELD|NK_EDIT_SIG_ENTER, text[7], &text_len[7], 64,  nk_filter_ascii);
    if (nk_button_label(context, "Submit") ||
        (active & NK_EDIT_COMMITED))
    {
        text[7][text_len[7]] = '\n';
        text_len[7]++;
        memcpy(&box_buffer[box_len], &text[7], (nk_size)text_len[7]);
        box_len += text_len[7];
        text_len[7] = 0;
    }


	nk_layout_row_end(context);

///** END EXAMPLE OF TEXT FIELDS
}

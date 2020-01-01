/*
 * main.c
 *
 *  Created on: 26 ���. 2019 �.
 *      Author: gstsvetkov
 */

#include <cstdio>
#include <cstdlib>
#include <cstdint>
//for treads
#include <thread>
#define NKC_IMPLEMENTATION
#include "nuklear_cross.h"

#include "enginer-dep.h"
#include "main-window.h"
#include "window-widget.h"

using namespace std;

void* gui_start(void *argp);

int main(int argc, char **argv) {
	printf("Running %s console\n", MY_NAME);

	printf("%s console ready\n", MY_NAME);

	printf("%s console start user interface\n", MY_NAME);

	TestWidget testWidget;

	list <WindowWidget*> ListWidgets;
	ListWidgets.push_back(&testWidget);

    MainWindow Window(&ListWidgets);

    Window.start();
    std::thread Twindow(MainWindow::execute, Window);
    Twindow.join();
	printf("%s console disable\n", MY_NAME);

	return 0;
}

enum radioOptions {
    EASY,
    HARD
};

struct my_nkc_app {
    struct nkc* nkcHandle;

    /* some user data */
    float value;
    enum radioOptions op;
};

void mainloop(void* loopArg){

	struct my_nkc_app* myapp = (struct my_nkc_app*)loopArg;
	struct nk_context *ctx = nkc_get_ctx(myapp->nkcHandle);

	union nkc_event e = nkc_poll_events(myapp->nkcHandle);
	if( (e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT) ){
		nkc_stop_main_loop(myapp->nkcHandle);
	}

	/* Nuklear GUI code */
	if (nk_begin(ctx, "Show", nk_rect(50, 50, 220, 220),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
		/* fixed widget pixel width */
		nk_layout_row_static(ctx, 30, 80, 1);
		if (nk_button_label(ctx, "button")) {
			/* event handling */
			printf("Button pressed\n");
		}

		/* fixed widget window ratio width */
		nk_layout_row_dynamic(ctx, 30, 2);
		if (nk_option_label(ctx, "easy", myapp->op == EASY)) myapp->op = EASY;
		if (nk_option_label(ctx, "hard", myapp->op == HARD)) myapp->op = HARD;

		/* custom widget pixel width */
		nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
		{
			nk_layout_row_push(ctx, 50);
			nk_label(ctx, "Volume:", NK_TEXT_LEFT);
			nk_layout_row_push(ctx, 110);
			nk_slider_float(ctx, 0, &(myapp->value), 1.0f, 0.1f);
		}
		nk_layout_row_end(ctx);
	}
	nk_end(ctx);
	/* End Nuklear GUI */

	nkc_render(myapp->nkcHandle, nk_rgb(40,40,40) );
}

void* gui_start(void *argp){
	struct my_nkc_app myapp;
	struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
	myapp.nkcHandle = &nkcx;
	/* init some user data */
	myapp.value = 0.4;
	myapp.op = HARD;

	if( nkc_init( myapp.nkcHandle, MY_NAME, 640, 480, NKC_WIN_FIXED ) ){
		printf("Successfull init. Starting user interface...\n");
		nkc_set_main_loop(myapp.nkcHandle, mainloop, (void*)&myapp );
	} else {
		printf("Can't init NKC\n");
	}
	printf("Value after exit = %f\n", myapp.value);
	nkc_shutdown( myapp.nkcHandle );
	return NULL;
}

/*
 * NoteWidget.cpp
 *
 *  Created on: 20 џэт. 2020 у.
 *      Author: gstsvetkov
 */

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include "NoteWidget.h"
#include "nuklear_cross.h"

using namespace std;

const int MEMORY_MARGIN = 1024;

NoteWidget::NoteWidget(std::string filename): filename(filename), textBufferEnd(0) {
	this->title = filename.c_str();
    this->hight = 400;
    this->widght = 400;
    this->x_pos = 10;
    this->y_pos = 10;
    this->flags = NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE;

    textBoxRect = {
            0,      //x position
            0,      //y position
            300,    //width
            300     //height
    };
//    textBoxRect = nk_get_null_rect();

    file.open((filename + ".txt"), fstream::in | fstream::out | fstream::app);
    if (file.is_open())
    {
    time_t startTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    file << ">>>>>>>>>>>>>>>>>" << endl;
    file << ctime(&startTime) << " " << title << endl;

    textBufferSize = file.tellg();
    textBufferEnd = textBufferSize;
    textBufferSize += MEMORY_MARGIN;

    textBuffer = new char[textBufferSize];
    memset(textBuffer, 0, textBufferSize);

    file.seekg(0, ios::beg);
    file.read(textBuffer, textBufferSize);
    file.close();
    }
}

NoteWidget::~NoteWidget() {

    time_t cur_time = chrono::system_clock::to_time_t(chrono::system_clock::now());

    UpdateFile(textBuffer);
    file.open((filename + ".txt"), fstream::out | fstream::app);

    file << ctime(&cur_time) << " end " << title << endl;
    file << "<<<<<<<<<<<<<<<<<" << endl;
	file.close();

	delete[] textBuffer;
	cout << "jurnal closed" << endl;
}

void NoteWidget::CustomDraw(struct nkc* nkcHandle){
    nk_flags flags;

    if (TextBufferExtension(textBufferEnd))
    	flags = NK_EDIT_BOX | NK_EDIT_GOTO_END_ON_ACTIVATE;
    else
    	flags = NK_EDIT_SELECTABLE | NK_EDIT_MULTILINE | NK_EDIT_ALLOW_TAB | NK_EDIT_CLIPBOARD;

    nk_layout_row_begin(context, NK_STATIC, textBoxRect.h - 10, 1);
    {
       nk_layout_row_push(context, textBoxRect.w - 10);
       nk_edit_string(context, flags, textBuffer, &textBufferEnd, textBufferSize-1, nk_filter_default);
    }
    nk_layout_row_end(context);

}

bool NoteWidget::TextBufferExtension(size_t endPosition)
{
    if ((textBufferSize - endPosition) >= MEMORY_MARGIN )
        return true;
    else
    {
        char* oldPtr = textBuffer;
        void* newPtr = realloc(textBuffer, textBufferSize + MEMORY_MARGIN);

        if (newPtr)
        {
            textBuffer = static_cast<char*>(newPtr);
            textBufferSize += MEMORY_MARGIN;
            return true;
        }
        else
        {
            textBuffer = oldPtr;
            return false;
        }
    }
}

bool NoteWidget::UpdateFile(char* buff)
{
    file.open((filename + ".txt"), fstream::in | fstream::out);
    if (!file.is_open())
        return false;

    string curString(buff);

    file << curString << endl;
    file.close();

    return true;
}

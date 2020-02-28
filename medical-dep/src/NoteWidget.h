/*
 * NoteWidget.h
 *
 *  Created on: 20 џэт. 2020 у.
 *      Author: gstsvetkov
 */

#ifndef NOTEWIDGET_H_
#define NOTEWIDGET_H_

#include <string>
#include <fstream>
#include <vector>
#include "window-widget.h"
#include "nuklear_cross.h"


class NoteWidget : public WindowWidget {
public:
	NoteWidget(std::string filename);
	virtual ~NoteWidget();
	void CustomDraw(struct nkc* nkcHandle);
private:
	std::string filename;
	std::fstream file;
	bool UpdateFile(char* buff);
	struct nk_rect textBoxRect;

	char* textBuffer;
	int textBufferSize;
	int textBufferEnd;
	bool TextBufferExtension(size_t endPosition);
};

#endif /* NOTEWIDGET_H_ */

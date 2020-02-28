/*
 * OutputConsole.h
 *
 *  Created on: 21 февр. 2020 г.
 *      Author: gstsvetkov
 */

#ifndef SRC_OUTPUTCONSOLE_H_
#define SRC_OUTPUTCONSOLE_H_

#include "window-widget.h"

class OutputConsole: public WindowWidget
{
public:
    OutputConsole();
    virtual ~OutputConsole();
private:
    void CustomDraw(struct nkc* nkcHandle);
};

#endif /* SRC_OUTPUTCONSOLE_H_ */

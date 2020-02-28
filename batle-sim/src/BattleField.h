/*
 * BattleField.h
 *
 *  Created on: 17 февр. 2020 г.
 *      Author: gstsvetkov
 */

#ifndef SRC_BATTLEFIELD_H_
#define SRC_BATTLEFIELD_H_

#include <string>
#include <list>
#include <vector>
#include "window-widget.h"
#include "nuklear_cross.h"

class BattleField: public WindowWidget{
public:
    BattleField(std::string name, unsigned int x, unsigned int y);
    virtual ~BattleField();

private:
    void CustomDraw(struct nkc* nkcHandle);

    enum state_t {
            CELL_STATE_EMPTY,
            CELL_STATE_BUSY,
            CELL_STATE_SHOT,
            CELL_STATE_MISS,
            CELL_STATE_MAX
    };

    struct cell{
            struct nk_rect rec;
            state_t state;
    };

    std::string TeamName;
    int scale;
    struct nk_color cellColor[CELL_STATE_MAX];
    std::list<std::list<cell>> battleMap;
};

#endif /* SRC_BATTLEFIELD_H_ */

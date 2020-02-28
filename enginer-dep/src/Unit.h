/*
 * Unit.h
 *
 *  Created on: 5 янв. 2020 г.
 *      Author: Геман
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "window-widget.h"
#include "nuklear_cross.h"
#include <string>
#include <cstdint>
#include <mutex>
#include <fstream>

namespace ship
{

using namespace std;

class Unit: public WindowWidget
{
public:
    typedef enum state {
        STATE_GOOD,
        STATE_WARN,
        STATE_BAD,
        STATE_MAX
    } state_t;

    Unit (void);
    Unit (string name,  int x, int y, int w, int h);
    ~Unit (void);

    uint32_t getState(void);
    void setState(state_t newState);
    string getName(void);

protected:
    void CustomDraw(struct nkc* nkcHandle);
private:
    void getImages(struct nkc* nkcHandle);

    string name;
    state_t state, lastState;
    struct nk_image imageGood;
    struct nk_image imageWarn;
    struct nk_image imageBad;

    std::mutex* mtxState;

    const std::string RESOURCES_DIR;
    const std::string IMAGE_FNAME_DEFAULT;
    const std::string IMAGE_FNAME_GOOD;
    const std::string IMAGE_FNAME_BAD;
    const std::string IMAGE_FNAME_WARN;
};

} /* namespace ship */

#endif /* UNIT_H_ */

/*
 * Ship.h
 *
 *  Created on: 5 янв. 2020 г.
 *      Author: Геман
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Unit.h"
#include <cstdint>
#include <list>

namespace ship
{
class Ship
{
public:
    Ship ();

    void execute (void);
    std::list <WindowWidget*>* getUnitsList(void);
private:

    void addUnit(string name, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    std::list <WindowWidget*> LstShipUnits;
};

} /* namespace ship */

#endif /* SHIP_H_ */

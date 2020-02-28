/*
 * Ship.cpp
 *
 *  Created on: 5 янв. 2020 г.
 *      Author: Геман
 */
#include <list>
#include <iterator>
#include <chrono>
#include <thread>
#include <iostream>
#include "Ship.h"
#include "Unit.h"

namespace ship
{
Ship::Ship (void)
{
    std::cout << "Scaning sheep modules:" << std::endl;
    addUnit("Hyperdrive", 10, 10, 100, 100);
    addUnit("Impeller", 10, 110, 100, 100);
    addUnit("Fuel tank", 110, 10, 100, 100);
    addUnit("Safety unit", 110, 110, 100, 100);
    addUnit("Life System", 210, 10, 100, 100);
    addUnit("Cargo cell", 210, 110, 100, 100);
	addUnit("Central control unit", 310, 10, 100, 100);
}

void Ship::execute(void)
{
    std::cout << "Ship scan running" << std::endl;
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::list<WindowWidget*>::iterator ItUnit;
        for (ItUnit = LstShipUnits.begin(); ItUnit != LstShipUnits.end(); ++ItUnit)
        {
        	std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "scan unit: ";
            Unit* unit = static_cast<Unit*>(*ItUnit);
            Unit::state_t state = static_cast<Unit::state_t>(unit->getState() + (1));
            if (state == Unit::STATE_MAX)
                state = Unit::STATE_GOOD;
            unit->setState(state);
            std::cout << unit->getName() << " state is " << state << std::endl;
        }
    }
}

std::list <WindowWidget*>* Ship::getUnitsList(void)
{
    return &LstShipUnits;
}

void Ship::addUnit(string name, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    Unit* unit = new Unit(name, x, y, w, h);
    LstShipUnits.push_back(unit);
}

} /* namespace ship */

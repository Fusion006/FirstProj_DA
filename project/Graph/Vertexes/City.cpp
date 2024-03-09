//
// Created by Pietrus on 08/03/2024.
//

#include "City.h"

#include <utility>

City::City(int id, std::string code, std::string name, int demand, int population)
{
    this->id = id;
    this->code = code;
    this->name = name;
    this->demand = demand;
    this->population = population;
}

#include "Station.h"

#include <utility>

Station::Station(int id, std::string code)
{
    this->id = id;
    this->code = std::move(code);
}

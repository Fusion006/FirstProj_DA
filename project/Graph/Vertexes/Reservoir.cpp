#include "Reservoir.h"

Reservoir::Reservoir(int id, std::string code, std::string name, std::string municipality, int capacity)
{
    this->id = id;
    this->code = code;
    this->name = name;
    this->municipality = municipality;
    this->capacity = capacity;
}

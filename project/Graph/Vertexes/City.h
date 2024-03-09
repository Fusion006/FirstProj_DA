#ifndef DAP1_CITY_H
#define DAP1_CITY_H


#include "Vertex.h"

class City : public Vertex{
private:
    std::string name;
    int demand;
    int population;
public:
    City(int id, std::string code, std::string name, int demand, int population);

};
#endif

#ifndef DAP1_RESERVOIR_H
#define DAP1_RESERVOIR_H


#include "Vertex.h"

class Reservoir : public Vertex{
private:
    std::string name;
    std::string municipality;
    int capacity;
public:
    Reservoir(int id, std::string code, std::string name, std::string municipality, int capacity);
};


#endif

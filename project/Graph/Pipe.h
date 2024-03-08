#ifndef DAP1_PIPE_H
#define DAP1_PIPE_H

#include "Vertexes/Vertex.h"

class Pipe {
private:
    Vertex* ServePointA;
    Vertex* ServePointB;
    int capacity;
public:
    Pipe(Vertex* ServePointA, Vertex* ServePointB, int capacity);

};


#endif

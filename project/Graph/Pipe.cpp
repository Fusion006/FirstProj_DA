#include "Pipe.h"

Pipe::Pipe(Vertex *ServePointA, Vertex *ServePointB, int capacity)
{
    this->ServePointA = ServePointA;
    this->ServePointB = ServePointB;
    this->capacity = capacity;
}

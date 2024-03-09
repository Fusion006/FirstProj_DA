#include "Vertex.h"
#include "../Pipe.h"

using namespace std;

string Vertex::get_code()
{
    return this->code;
}

int Vertex::get_id()
{
    return this->id;
}

bool Vertex::get_visited() {
    return this->visited;
}

void Vertex::set_visited(bool state) {
    this->visited = state;
}

void Vertex::add_pipe(Pipe* newPipe)
{
    this->pipes.push_back(newPipe);
}

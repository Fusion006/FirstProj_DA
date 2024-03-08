#ifndef DAP1_VERTEX_H
#define DAP1_VERTEX_H
#include <iostream>
#include <vector>

class Pipe;

class Vertex
    {
protected:
    int id;
    std::string code;
    bool visited;
    std::vector<Pipe*> pipes;

public:
    int get_id();
    std::string get_code();
    bool get_visited();
    void set_visited(bool state);
    void add_pipe(Pipe* newPipe);
    void remove_pipe(); //TODO add arguments (not relevant now for parsing)

};


#endif //DAP1_VERTEX_H

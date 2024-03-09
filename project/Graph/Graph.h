#ifndef DAP1_GRAPH_H
#define DAP1_GRAPH_H

#include <string>
#include <vector>
using namespace std;
class Pipe;

/************************* Vertex  **************************/
class Vertex {
    string get_code();
    int get_id();
    [[nodiscard]] vector<Pipe *> getAdj() const;
    [[nodiscard]] bool isVisited() const;
    [[nodiscard]] bool isProcessing() const;
    [[nodiscard]] unsigned int getIndegree() const;
    [[nodiscard]] double getDist() const;
    [[nodiscard]] Pipe* getPath() const;
    [[nodiscard]] vector<Pipe*> getIncoming() const;

    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int newIndegree);
    void setDist(int dist);
    void setPath(Pipe *path);
    Pipe* addPipe(Vertex *dest, int capacity);
    bool removePipe(const string& code);
    void removeOutgoingPipes();

protected:
    int id;
    string code;
    vector<Pipe*> adj;  // outgoing edges

// auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    Pipe *path = nullptr;

    vector<Pipe *> incoming; // incoming edges

    void deletePipe(Pipe* pipe);
};

/********************** City  ****************************/
class City : public Vertex{
private:
    std::string name;
    int demand;
    int population;
public:
    City(int id, std::string code, std::string name, int demand, int population);
    //TODO add getters and setters
};

/********************** Reservoir  ****************************/
class Reservoir : public Vertex{
private:
    std::string name;
    std::string municipality;
    int capacity;
public:
    Reservoir(int id, std::string code, std::string name, std::string municipality, int capacity);
    //TODO add getters and setters
};

/********************** Station  ****************************/
class Station : public Vertex{
private:

public:
    Station(int id, std::string code);
    //TODO add getters and setters
};

/********************** Pipe  ****************************/
class Pipe {
public:
    Pipe(Vertex* orig, Vertex* dest, double w);

    [[nodiscard]] Vertex* getDest() const;
    [[nodiscard]] double getCapacity() const;
    [[nodiscard]] double getFlow() const;
    [[nodiscard]] bool isSelected() const;
    [[nodiscard]] Vertex* getOrig() const;
    [[nodiscard]] Pipe* getReverse() const;

    void setSelected(bool selected);
    void setReverse(Pipe* reverse);
    void setFlow(double flow);
protected:
    Vertex* dest; // destination vertex
    double capacity; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Pipe *reverse = nullptr;

    double flow = 0; // for flow-related problems
};

/********************** Graph  ****************************/
class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const string &code) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addCity(int id, std::string code, std::string name, int demand, int population);//TODO
    bool addReservoir(int id, std::string code, std::string name,
                      std::string municipality, int capacity);
    bool addStation(int id, std::string code);
    bool removeVertex(const string &code);//TODO

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addPipe(const string &sourceCode, const string &destCode, double cap);
    bool removePipe(const string &sourceCode, const string &destCode);
    bool addBidirectionalPipe(const string &sourceCode, const string &destCode, double cap);

    int getNumVertex() const;
    std::vector<Vertex*> getVertexSet() const;

    vector<string> dfs() const;
    vector<string> dfs(const string & source) const;
    void dfsVisit(Vertex *v,  std::vector<string> & res) const;
    vector<string> bfs(const string& source) const;

    bool isDAG() const;
    bool dfsIsDAG(Vertex *v) const;
    std::vector<string> topsort() const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    //double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    //int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
    //TODO descobrir se isto é preciso
};

//void deleteMatrix(int **m, int n);
//void deleteMatrix(double **m, int n);
//TODO descobrir se isto é preciso


/************************* Vertex  **************************/

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Pipe* Vertex::addPipe(Vertex *dest, int capacity) {
    auto newPipe = new Pipe(this, dest, capacity);
    adj.push_back(newPipe);
    dest->incoming.push_back(newPipe);
    return newPipe;
}
/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removePipe(const string& Vertex_code) {
    bool removedPipe = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Pipe *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->get_code() == Vertex_code) {
            it = adj.erase(it);
            deletePipe(edge);
            removedPipe = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedPipe;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
void Vertex::removeOutgoingPipes() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Pipe *edge = *it;
        it = adj.erase(it);
        deletePipe(edge);
    }
}

/*bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}*///TODO adiconar se usarmos MutablePriorityQueue

string Vertex::get_code() {
    return this->code;
}
vector<Pipe*> Vertex::getAdj() const {
    return this->adj;
}
bool Vertex::isVisited() const {
    return this->visited;
}
bool Vertex::isProcessing() const {
    return this->processing;
}
unsigned int Vertex::getIndegree() const {
    return this->indegree;
}
double Vertex::getDist() const {
    return this->dist;
}
Pipe* Vertex::getPath() const {
    return this->path;
}
vector<Pipe*> Vertex::getIncoming() const {
    return this->incoming;
}
void Vertex::setVisited(bool state) {
    this->visited = state;
}
void Vertex::setProcesssing(bool state) {
    this->processing = state;
}
void Vertex::setIndegree(unsigned int newIndegree) {
    this->indegree = newIndegree;
}
void Vertex::setDist(int distance) {
    this->dist = distance;
}
void Vertex::setPath(Pipe* new_path) {
    this->path = new_path;
}
void Vertex::deletePipe(Pipe* edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->get_code() == this->code) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Pipe  ****************************/
Pipe::Pipe(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), capacity(w) {}
Vertex * Pipe::getDest() const {
    return this->dest;
}
double Pipe::getCapacity() const {
    return this->capacity;
}
Vertex * Pipe::getOrig() const {
    return this->orig;
}
Pipe *Pipe::getReverse() const {
    return this->reverse;
}
bool Pipe::isSelected() const {
    return this->selected;
}
double Pipe::getFlow() const {
    return flow;
}
void Pipe::setSelected(bool state) {
    this->selected = state;
}
void Pipe::setReverse(Pipe *reversePipe) {
    this->reverse = reversePipe;
}
void Pipe::setFlow(double new_flow) {
    this->flow = new_flow;
}


/*
#include <map>
#include "Vertexes/Vertex.h"
#include "Pipe.h"
#include "Vertexes/City.h"
#include "Vertexes/Reservoir.h"
#include "Vertexes/Station.h"
#include "fstream"
#include "sstream"

class Graph {
private:
    std::map<std::string ,City*> cities;
    std::map<std::string,Reservoir*> reservoirs;
    std::map<std::string,Station*> stations;
    std::map<std::string,std::string> nameToCode;

public:
    Graph();

};

*/
#endif

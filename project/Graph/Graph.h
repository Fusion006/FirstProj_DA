#ifndef DAP1_GRAPH_H
#define DAP1_GRAPH_H

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <map>

using namespace std;
class Pipe;

/************************* Vertex  **************************/
class Vertex {
public:
    [[nodiscard]] inline vector<Pipe *> getAdj() const;
    [[nodiscard]] inline bool isVisited() const;
    [[nodiscard]] inline bool isProcessing() const;
    [[nodiscard]] inline unsigned int getIndegree() const;
    [[nodiscard]] inline double getDist() const;
    [[nodiscard]] inline Pipe* getPath() const;
    [[nodiscard]] inline vector<Pipe*> getIncoming() const;

    int get_id();
    string get_code();
    void setVisited(bool state);
    void setProcesssing(bool state);
    void setIndegree(unsigned int newIndegree);
    void setDist(int dist);
    void setPath(Pipe *path);
    Pipe* addPipe(Vertex *dest, double capacity);
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

    void deletePipe(Pipe* edge);
};

/********************** City  ****************************/
class City : public Vertex{
private:
    string name;
    int demand;
    int population;
public:
    City(int id, std::string code, string name, int demand, int population)
    {
        this->id=id;
        this->code=std::move(code);
        this->name=std::move(name);
        this->demand=demand;
        this->population=population;
    }
    [[nodiscard]] inline string get_name() const {return this->name;}
    [[nodiscard]] inline int get_demand() const {return this->demand;}
    [[nodiscard]] inline int get_population() const { return this->population;}
};

/********************** Reservoir  ****************************/
class Reservoir : public Vertex{
private:
    std::string name;
    std::string municipality;
    int capacity;
public:
    Reservoir(int id, std::string code, std::string name, std::string municipality, int capacity){
        this->id = id;
        this->code = std::move(code);
        this->name = std::move(name);
        this->municipality = std::move(municipality);
        this->capacity = capacity;
    }
    //TODO add getters and setters
};

/********************** Station  ****************************/
class Station : public Vertex{
private:

public:
    Station(int id, std::string code){
        this->id = id;
        this->code = std::move(code);
    }
    //TODO add getters and setters
};

/********************** Pipe  ****************************/
class Pipe {
public:
    Pipe(Vertex* orig, Vertex* dest, double w);

    [[nodiscard]] inline Vertex* getDest() const;
    [[nodiscard]] inline double getCapacity() const;
    [[nodiscard]] inline double getFlow() const;
    [[nodiscard]] inline bool isSelected() const;
    [[nodiscard]] inline Vertex* getOrig() const;
    [[nodiscard]] inline Pipe* getReverse() const;

    void setSelected(bool state);
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
    Graph();
    //~Graph(); TODO adicionar se usarmos Floyd-Warshall
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    [[nodiscard]] inline Vertex *findVertex(const string &code) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addCity(int id, const std::string& code, std::string name, int demand, int population);//TODO
    bool addReservoir(int id, const std::string& code, std::string name,
                      std::string municipality, int capacity);
    bool addStation(int id, const std::string& code);
    bool removeVertex(const string &code);//TODO

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addPipe(const string &sourceCode, const string &destCode, double cap);
    bool removePipe(const string &sourceCode, const string &destCode);
    bool addBidirectionalPipe(const string &sourceCode, const string &destCode, double cap);

    [[nodiscard]] inline size_t getNumVertex() const;
    [[nodiscard]] inline std::vector<Vertex*> getVertexSet() const;

    [[nodiscard]] inline vector<string> dfs() const;
    [[nodiscard]] inline vector<string> dfs(const string & source) const;
    void dfsVisit(Vertex *v,  std::vector<string> & res) const;
    [[nodiscard]] inline vector<string> bfs(const string& source) const;

    [[nodiscard]] inline bool isDAG() const;
    bool dfsIsDAG(Vertex *v) const;
    [[nodiscard]] inline std::vector<string> topsort() const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    //double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    //int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
    //TODO descobrir se isto é preciso

public:
    map<string,string> cityToCode;
};

//void deleteMatrix(int **m, int n);
//void deleteMatrix(double **m, int n);
//TODO descobrir se isto é preciso


/************************* Vertex  **************************/

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
inline Pipe* Vertex::addPipe(Vertex *dest, double capacity) {
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
inline bool Vertex::removePipe(const string& Vertex_code) {
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
inline void Vertex::removeOutgoingPipes() {
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

inline string Vertex::get_code() {
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
inline void Vertex::setVisited(bool state) {
    this->visited = state;
}
inline void Vertex::setProcesssing(bool state) {
    this->processing = state;
}
inline void Vertex::setIndegree(unsigned int newIndegree) {
    this->indegree = newIndegree;
}
inline void Vertex::setDist(int distance) {
    this->dist = distance;
}
inline void Vertex::setPath(Pipe* new_path) {
    this->path = new_path;
}
inline void Vertex::deletePipe(Pipe* edge) {
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
inline Pipe::Pipe(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), capacity(w) {}
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
inline void Pipe::setSelected(bool state) {
    this->selected = state;
}
inline void Pipe::setReverse(Pipe *reversePipe) {
    this->reverse = reversePipe;
}
inline void Pipe::setFlow(double new_flow) {
    this->flow = new_flow;
}

/********************** Graph  ****************************/


size_t Graph::getNumVertex() const {
    return vertexSet.size();
}
std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}
/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const string &code) const {
    for (Vertex* v : vertexSet)
        if (v->get_code() == code)
            return v;
    return nullptr;
}

/*
 *  Adds a vertex to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */


inline bool Graph::addCity(int id, const std::string& code, std::string name, int demand, int population) {
    if (findVertex(code) != nullptr) return false;
    vertexSet.push_back(new City(id,code,std::move(name),demand,population));
    return true;
}
inline bool Graph::addReservoir(int id, const std::string& code, std::string name,
                  std::string municipality, int capacity){
    if (findVertex(code) != nullptr) return false;
    vertexSet.push_back(new Reservoir(id,code,std::move(name),std::move(municipality),capacity));
    return true;
}
inline bool Graph::addStation(int id, const std::string& code){
    if (findVertex(code) != nullptr) return false;
    vertexSet.push_back(new Station(id,code));
    return true;
}

/*
 *  Removes a vertex from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */

inline bool Graph::removeVertex(const string &code) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->get_code() == code) {
            auto v = *it;
            v->removeOutgoingPipes();
            for (auto u : vertexSet) {
                u->removePipe(v->get_code());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge capacity.
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
inline bool Graph::addPipe(const std::string &sourceCode, const std::string &destCode, double cap) {
    auto v1 = findVertex(sourceCode);
    auto v2 = findVertex(destCode);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addPipe(v2, cap);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
inline bool Graph::removePipe(const std::string &sourceCode, const std::string &destCode) {
    Vertex * srcVertex = findVertex(sourceCode);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removePipe(destCode);
}


inline bool Graph::addBidirectionalPipe(const std::string &sourceCode, const std::string &destCode, double cap) {
    auto v1 = findVertex(sourceCode);
    auto v2 = findVertex(destCode);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addPipe(v2, cap);
    auto e2 = v2->addPipe(v1, cap);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/****************** DFS ********************/

/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 */
vector<string> Graph::dfs() const {
    std::vector<string> res;
    for (Vertex* v : vertexSet)
        v->setVisited(false);
    for (Vertex* v : vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

/*
 * Performs a depth-first search (dfs) in a graph (this) from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */

vector<string> Graph::dfs(const string & source) const {
    std::vector<string> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    // Perform the actual DFS using recursion
    dfsVisit(s, res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */

inline void Graph::dfsVisit(Vertex *v, vector<string> & res) const {
    v->setVisited(true);
    res.push_back(v->get_code());
    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */

vector<string> Graph::bfs(const string & source) const {
    std::vector<string> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }

    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }

    // Perform the actual BFS using a queue
    std::queue<Vertex *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->get_code());
        for (auto & e : v->getAdj()) {
            auto w = e->getDest();
            if ( ! w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */


bool Graph::isDAG() const {
    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setProcesssing(false);
    }
    for (auto v : vertexSet) {
        if (! v->isVisited()) {
            if ( ! dfsIsDAG(v) ) return false;
        }
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */

inline bool Graph::dfsIsDAG(Vertex *v) const {
    v->setVisited(true);
    v->setProcesssing(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (w->isProcessing()) return false;
        if (! w->isVisited()) {
            if (! dfsIsDAG(w)) return false;
        }
    }
    v->setProcesssing(false);
    return true;
}

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

inline vector<string> Graph::topsort() const{
    std::vector<string> res;

    for (auto v : vertexSet) {
        v->setIndegree(0);
    }
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    std::queue<Vertex *> q;
    for (auto v : vertexSet) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while( !q.empty() ) {
        Vertex * v = q.front();
        q.pop();
        res.push_back(v->get_code());
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if(w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if ( res.size() != vertexSet.size() ) {
        //std::cout << "Impossible topological ordering!" << std::endl;
        res.clear();
        return res;
    }

    return res;
}
/*
inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}


Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}
*///TODO importante so se usarmos Floyd-Warshall
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
    std::map<std::string,std::string> cityToCode;

public:
    Graph();

};

*/
#endif

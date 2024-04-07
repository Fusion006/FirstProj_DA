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
/**
 * @class Vertex
 * @brief Generic function that represents a Graphs Vertex
 */
class Vertex {
public:

    Vertex(int id, string code){
        this->id = id;
        this->code = std::move(code);
    }

    [[nodiscard]] inline vector<Pipe *> getAdj() const;
    void inline setAdj(vector<Pipe*> newAdj);
    [[nodiscard]] inline bool isVisited() const;
    [[nodiscard]] inline bool isProcessing() const;
    [[nodiscard]] inline unsigned int getIndegree() const;
    [[nodiscard]] inline double getDist() const;
    [[nodiscard]] inline Pipe* getPath() const;
    [[nodiscard]] inline vector<Pipe*> getIncoming() const;
    [[nodiscard]] int get_id() const;

    string get_code();
    void setVisited(bool state);
    void setProcesssing(bool state);
    void setIndegree(unsigned int newIndegree);
    void setDist(int dist);
    void setPath(Pipe *path);
    Pipe* addPipe(Vertex *dest, double capacity);
    bool removePipe(const string& code);
    void removeOutgoingPipes();
    bool operator<(Vertex & vertex) const;
protected:
    int id;
    string code;
    vector<Pipe*> adj;  // outgoing edges

// auxiliary fields
    bool visited = false;
    bool processing = false;
    unsigned int indegree = 0;
    double dist = 0;
    Pipe *path = nullptr;

    vector<Pipe *> incoming; // incoming edges

    void deletePipe(Pipe* edge);
};

/********************** City  ****************************/
/**
 * @class City
 * @Brief A extension of the Vertex class that represents a City it adds the name, demand and population parameters
 */
class City : public Vertex{
private:
    string name;
    int demand;
    int population;
public:

    City(int id, std::string code, string name, int demand, int population) : Vertex(id, std::move(code))
    {
        this->name=std::move(name);
        this->demand=demand;
        this->population=population;
    }

    [[nodiscard]] inline string get_name() const {return this->name;}
    [[nodiscard]] inline int get_demand() const {return this->demand;}
    [[nodiscard]] inline int get_population() const { return this->population;}
};

/********************** Reservoir  ****************************/
/**
 * @class Reservoir
 * @Brief A extension of the Vertex class that represents a Reservoir it adds the name, municipality and capacity parameters
 */
class Reservoir : public Vertex{
private:
    std::string name;
    std::string municipality;
    double capacity;
public:

    Reservoir(int id, std::string code, std::string name, std::string municipality, int capacity) : Vertex(id, std::move(code)){
        this->name = std::move(name);
        this->municipality = std::move(municipality);
        this->capacity = capacity;
    }

    [[nodiscard]] inline int getId() const {
        return id;
    }

    [[nodiscard]] inline std::string getCode() const {
        return code;
    }

    [[nodiscard]] inline std::string getName() const {
        return name;
    }

    [[nodiscard]] inline std::string getMunicipality() const {
        return municipality;
    }

    [[nodiscard]] inline double getCapacity() const {
        return capacity;
    }

    inline void setCapacity(double newCapacity) {
        this->capacity = newCapacity;
    }
};

/********************** Station  ****************************/
/**
 * @class Station
 * @Brief A extension of the Vertex class that represents a Pumping Station
 * This class does not add any parameters to the Vertex class yet it it useful to distinguish a Pumping Station from other Vertexes
 */
class Station : public Vertex{
private:

public:

    Station(int id, std::string code) : Vertex(id, std::move(code)) {}

    [[nodiscard]] inline int getId() const {
        return id;
    }

    // Getter for code
    [[nodiscard]] inline const std::string& getCode() const {
        return code;
    }
};

/********************** Pipe  ****************************/
/**
 * @class Pipe
 * @Brief A representation of the Graphs edges, in this case, they represent pipelines to move the water across the network
 */
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
    void setCapacity(double capacity);

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
/**
 * @class Graph
 * @brief Class that represents the dataset as a graph
 */
class Graph {
public:
    Graph();
    [[nodiscard]] inline Vertex *findVertex(const string &code) const;
    [[nodiscard]] inline Reservoir *findReservoir(const string &code) const;
    [[nodiscard]] inline Station *findStation(const string &code) const;
    [[nodiscard]] inline City *findCity(const string &code) const;
    [[nodiscard]] inline Pipe *findPipe(const string &source, const string &target) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addCity(int id, const std::string& code, std::string name, int demand, int population);
    bool addReservoir(int id, const std::string& code, std::string name, std::string municipality, int capacity);
    bool addStation(int id, const std::string& code);
    bool addVertex(int id, const std::string& code);
    bool removeVertex(const string &code);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    [[nodiscard]] bool addPipe(const string &sourceCode, const string &destCode, double cap) const;
    [[nodiscard]] bool removePipe(const string &sourceCode, const string &destCode) const;
    [[nodiscard]] bool addBidirectionalPipe(const string &sourceCode, const string &destCode, double cap) const;

    [[nodiscard]] inline size_t getNumVertex() const;
    [[nodiscard]] inline std::vector<Vertex*> getVertexSet() const;
    [[nodiscard]] inline std::vector<Reservoir*> getReservoirs() const;
    [[nodiscard]] inline std::vector<City*> getCities() const;
    [[nodiscard]] inline std::vector<Station*> getStations() const;


    [[nodiscard]] inline vector<string> dfs() const;
    [[nodiscard]] inline vector<string> dfs(const string & source) const;
    void dfsVisit(Vertex *v,  std::vector<string> & res) const;
    [[nodiscard]] inline vector<string> bfs(const string& source) const;

protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    vector<Reservoir*> reservoirs;
    vector<Station*> stations;
    vector<City*> cities;

public:
    map<string,string> cityToCode;

};

/* Vertex */

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
inline Pipe* Vertex::addPipe(Vertex *dest, double capacity) {
    auto newPipe = new Pipe(this, dest, capacity);
    adj.push_back(newPipe);
    dest->incoming.push_back(newPipe);
    dest->setIndegree(dest->getIndegree()+1);
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

inline bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

inline string Vertex::get_code() {
    return this->code;
}

inline int Vertex::get_id() const {
    return this->id;
}

vector<Pipe*> Vertex::getAdj() const {
    return this->adj;
}
void Vertex::setAdj(vector<Pipe*> newAdj) {
    this->adj = std::move(newAdj);
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

/* Pipe */
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

inline void Pipe::setCapacity(double newCapacity) {
    this->capacity = newCapacity;
}

/* Graph */


size_t Graph::getNumVertex() const {
    return vertexSet.size();
}
std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

std::vector<Reservoir*> Graph::getReservoirs() const {
    return reservoirs;
}

std::vector<City*> Graph::getCities() const {
    return cities;
}

std::vector<Station*> Graph::getStations() const {
    return stations;
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

Reservoir * Graph::findReservoir(const string &code) const {
    for (Reservoir* v : reservoirs)
        if (v->get_code() == code)
            return v;
    return nullptr;
}

Station * Graph::findStation(const string &code) const {
    for (Station* v : stations)
        if (v->get_code() == code)
            return v;
    return nullptr;
}

City * Graph::findCity(const string &code) const {
    for (City* v : cities)
        if (v->get_code() == code)
            return v;
    return nullptr;
}

inline bool Graph::addCity(int id, const std::string& code, std::string name, int demand, int population) {
    if (findVertex(code) != nullptr) return false;
    auto* newCity = new City(id,code,std::move(name),demand,population);
    vertexSet.push_back(newCity);
    cities.push_back(newCity);

    return true;
}
inline bool Graph::addReservoir(int id, const std::string& code, std::string name,
                  std::string municipality, int capacity){
    if (findVertex(code) != nullptr) return false;
    auto* newReservoir = new Reservoir(id,code,std::move(name),std::move(municipality),capacity);
    vertexSet.push_back(newReservoir);
    reservoirs.push_back(newReservoir);
    return true;
}
inline bool Graph::addStation(int id, const std::string& code){
    if (findVertex(code) != nullptr) return false;
    auto* newStation = new Station(id,code);
    vertexSet.push_back(newStation);
    stations.push_back(newStation);
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
inline bool Graph::addPipe(const std::string &sourceCode, const std::string &destCode, double cap) const {
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
inline bool Graph::removePipe(const std::string &sourceCode, const std::string &destCode) const {
    Vertex * srcVertex = findVertex(sourceCode);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removePipe(destCode);
}


inline bool Graph::addBidirectionalPipe(const std::string &sourceCode, const std::string &destCode, double cap) const {
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

/* DFS */

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

/* BFS */
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


inline bool Graph::addVertex(int id, const string &code) {
    if(findVertex(code) != nullptr) return false;
    auto* newVertex = new Vertex(id, code);
    vertexSet.push_back(newVertex);
    return true;
}

Pipe *Graph::findPipe(const string &source, const string &target) const {
    auto vsource = findVertex(source);
    if (vsource == nullptr) {
        return nullptr;
    }
    for (auto pipe : vsource->getAdj()) {
        if (pipe->getDest()->get_code() == target) {
            return pipe;
        }
    }
    return nullptr;
}
#endif

#include "reliability.h"
using namespace std;

map<string,int> getReservoirMap(Graph &g)
{
    map<string,int> res;
    vector<Vertex*> vertexSet = g.getVertexSet();
    for(Vertex* v : vertexSet)
    {
        if (v->get_code()[0] == 'R')
        {
            //res[v->get_code()] = v->getCapacity();
        }
    }
}

string getReservoirInput(Graph &g)
{
    string code;
    std::cout << "Reservoir code to be removed:";
    cin>>code;
    Vertex* removed = g.findVertex(code);
    if ( removed == nullptr || code.empty() || code[0] != 'R')
    {
        cout<<"No Reservoir with that code";
        return "";
    }
    return removed->get_code();
}

map<string,int> removeReservoir(Graph &g, set<string>)
{
//TODO codigo do maxflow
}

void remReservoirController(Graph& g)
{
    map<string,int> res_to_capacity = getReservoirMap(g);
    set<string> removed;
    map<string,int> map = removeReservoir(g,removed);
    string removedRes;
    while (removedRes.empty())
    {
        removedRes = getReservoirInput(g);
    }
    removed.insert(removedRes);



}
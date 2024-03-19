#include "reliability.h"
using namespace std;



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
    set<string> removed;
    map<string,int> map = removeReservoir(g,removed);
    string removedRes;
    while (removedRes.empty())
    {
        removedRes = getReservoirInput(g);
    }
    removed.insert(removedRes);



}
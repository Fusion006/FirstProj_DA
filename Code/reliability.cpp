#include "reliability.h"
using namespace std;

map<string,int> getReservoirMap(Graph &g)
{
    map<string,int> res;
    vector<Reservoir*> reservoirs = g.getReservoirs();
    for(Reservoir* v : reservoirs)
    {
        res[v->getCode()] = v->getCapacity();
    }
    return res;
}

void printDiferences(Graph& g, const map<string,int>& start,map<string,int> end)
{
    int totalDif = 0;
    cout<<"Flow Decreased in this cities:\n";
    for (pair<string, int> p : start)
    {
        if (p.second > end.at(p.first))
        {
            City* affectedCity = g.findCity(p.first);
            cout<<affectedCity->get_name() << " from "<< p.second <<" to " << end.at(p.first);
            if (end.at(p.first) < affectedCity->get_demand())
                cout<<"Demand not met\n";
            else
                cout<<endl;

            totalDif += (p.second - end.at(p.first));
        }
    }
    cout<<"Total decrease: "<<totalDif<<endl;
}

Reservoir* getReservoirInput(Graph &g)
{
    string code;
    Reservoir* removed;
    while (code.empty()) {
        std::cout << "Reservoir code to be removed:";
        cin >> code;
        removed = g.findReservoir(code);
        if (removed == nullptr){
            cout << "No Reservoir with that code\n";
            code = "";
        }
    }
    return removed;
}

bool checkRelevantVertex(Graph &g, Vertex* v)
{
    for(Vertex* vertex : g.getVertexSet())
        vertex->setVisited(false);

    queue<Vertex*> q;
    q.push(v);
    while(!q.empty())
    {
        Vertex* newVertex = q.front();
        q.pop();
        newVertex->setVisited(true);
        for (Pipe* p : newVertex->getAdj())
        {
            Vertex* dest = p->getDest();
            if(p->getFlow() != 0 and !dest->isVisited())
            {
                if (dest->get_code()[0] == 'C') return true;
                q.push(dest);
            }
        }
    }
    return false;
}



void restoreReservoir(Graph &g,  map<string,int>& capacities)
{
    vector<Reservoir*> reservoirs = g.getReservoirs();
    for(Reservoir* v : reservoirs)
    {
        v->setCapacity(capacities.at(v->get_code()));
    }
}

void remReservoirController(Graph& g)
{
    //TODO change GET_Reservoir/cities functions
    map<string,int> initial_res_to_capacity = getReservoirMap(g);
    map<string,int> previous_city_to_flow = {};//TODO maxFlow;

    Reservoir* reservoir;
    bool finished = false;
    string option;

    while(!finished)
    {
        reservoir = getReservoirInput(g);
        reservoir->setCapacity(0);

        if (!checkRelevantVertex(g,reservoir)){
            cout<<"That Reservoir removal doesn't affect performance\n";
        }else{
            reservoir->setCapacity(0);
            map<string,int> new_city_to_flow;//TODO = maxFow();
            printDiferences(g, previous_city_to_flow, new_city_to_flow);
            previous_city_to_flow = new_city_to_flow;
            cout<<"Do you want to remove another one?[Y/n]:";
            cin>>option;
            if (option == "Y") finished = true;
        }
    }
    restoreReservoir(g,initial_res_to_capacity);
}
#include "reliability.h"
#include "FlowNetwork.h"

using namespace std;

double getCityDeficit(const string& cityName, const vector<pair<City*, double>>& cityToDeficit)
{
    for(pair<City*, double> pair : cityToDeficit)
    {
        if (cityName == pair.first->get_code())
        {
            return pair.second;
        }
    }
    return 0;
}
map<string,double> getReservoirMap(Graph &g)
{
    map<string,double> res;
    vector<Reservoir*> reservoirs = g.getReservoirs();
    for(Reservoir* v : reservoirs)
    {
        res[v->getCode()] = v->getCapacity();
    }
    return res;
}
void printDifferences( const vector<pair<City*, double>>& start, const vector<pair<City*, double>>& end)
{
    double totalDif = 0;
    cout<<"Flow Decreased in this cities:\n";
    for (pair<City*, double> cityDeficit : end)
    {
        double oldDeficit = getCityDeficit(cityDeficit.first->get_code(),start);
        double newDeficit = cityDeficit.second;

        if (newDeficit > oldDeficit )
        {
            City* city = cityDeficit.first;
            cout << city->get_name() << " demand not met by: " << newDeficit << "\n";
            totalDif += newDeficit-oldDeficit;
        }
    }
    cout<<"The removal of this reservoir caused an additional deficit of " << totalDif << "\n";
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
void restoreReservoir(Graph &g, const map<string,double>& capacities)
{
    vector<Reservoir*> reservoirs = g.getReservoirs();
    for(Reservoir* v : reservoirs)
    {
        v->setCapacity(capacities.at(v->get_code()));
    }
}
void remReservoir(Graph& g)
{
    //TODO change GET_Reservoir/cities functions
    map<string,double> initial_res_to_capacity = getReservoirMap(g);

    FlowNetworkEvaluation(g);
    vector<pair<City*, double>> previous_city_in_deficit = getCitiesInDeficit(g);

    Reservoir* reservoir;
    bool finished = false;
    string option;
    size_t remReservoirs = 0;
    size_t maxReservoirs = g.getReservoirs().size();

    while(!finished && remReservoirs != maxReservoirs)
    {
        reservoir = getReservoirInput(g);

        if (!checkRelevantVertex(g,reservoir)){
            cout<<"That Reservoir removal doesn't affect performance\n";
        }else{
            reservoir->setCapacity(0);
            remReservoirs++;

            FlowNetworkEvaluation(g);
            vector<pair<City*, double>> new_city_in_deficit = getCitiesInDeficit(g);

            printDifferences(previous_city_in_deficit, new_city_in_deficit);
            previous_city_in_deficit = new_city_in_deficit;
            cout<<"Do you want to remove another reservoir?[Y/n]:";
            cin>>option;
            if (option != "Y") finished = true;
        }
    }
    if (maxReservoirs==remReservoirs) cout<<"All reservoirs were removed\n";
    restoreReservoir(g,initial_res_to_capacity);
}


Station* getStationInput(Graph &g)
{
    string code;
    Station* removed;
    while (code.empty()) {
        std::cout << "Station code to be removed:";
        cin >> code;
        removed = g.findStation(code);
        if (removed == nullptr){
            cout << "No station with that code\n";
            code = "";
        }
    }
    return removed;
}
void remStation(Graph& g)
{
    map<pair<string,string>,double> stationsPipes;
    FlowNetworkEvaluation(g);

    vector<pair<City*, double>> previous_city_in_deficit = getCitiesInDeficit(g);
    Station* station;
    bool finished = false;
    string option;
    size_t remStations = 0;
    size_t maxStations = g.getStations().size();

    while(!finished && remStations != maxStations)
    {
        station = getStationInput(g);

        if (!checkRelevantVertex(g,station)){
            cout<<"That Station removal doesn't affect performance\n";
        }else{
            for (Pipe* pipe : station->getAdj())
            {
                stationsPipes[{station->getCode(),pipe->getDest()->get_code()}] = pipe->getCapacity();
                pipe->setCapacity(0);
            }

            remStations++;
            FlowNetworkEvaluation(g);
            vector<pair<City*, double>> new_city_in_deficit = getCitiesInDeficit(g);

            printDifferences(previous_city_in_deficit, new_city_in_deficit);
            previous_city_in_deficit = new_city_in_deficit;
            cout<<"Do you want to remove another station?[Y/n]:";
            cin>>option;
            if (option != "Y") finished = true;
            if (maxStations==remStations) cout<<"All stations were removed\n";
        }
    }
    restorePipes(g, stationsPipes);
}
bool deficitIncreased(const vector<pair<City*, double>>& start, const vector<pair<City*, double>>& end)
{
    if (start.size() != end.size()) return true;

    double newDeficit;
    for (pair<City*, double> endDeficit : end)
    {
        double oldDeficit = getCityDeficit(endDeficit.first->get_code() ,start);
        newDeficit = endDeficit.second;
        if (newDeficit > oldDeficit)
        {
            return true;
        }
    }

    return false;
}
void printIrrelevantStations(const set<string>& stations)
{
    cout<<"There are "<<stations.size()<<" irrelevant stations:\n";
    for (const string& station : stations)
    {
        cout << station << '\t';
    }
}
bool isStationIrrelevant(Graph& g, Station* station)
{
    FlowNetworkEvaluation(g);
    if (! checkRelevantVertex(g,station)) return false;
    vector<pair<City*, double>> previous_city_in_deficit = getCitiesInDeficit(g);


    map<pair<string,string>,double> stationsPipes;
    for (Pipe* pipe : station->getAdj())
    {
        stationsPipes[{station->getCode(),pipe->getDest()->get_code()}] = pipe->getCapacity();
        pipe->setCapacity(0);
    }
    FlowNetworkEvaluation(g);
    vector<pair<City*, double>> new_city_in_deficit = getCitiesInDeficit(g);

    restorePipes(g,stationsPipes);
    if (deficitIncreased(previous_city_in_deficit, new_city_in_deficit)) return false;
    return true;
}
void findIrrelevantStations(Graph& g)
{
    set<string> res;
    for (Station* station : g.getStations())
    {
        if (isStationIrrelevant(g,station))
        {
            res.insert(station->getCode());
        }
    }
    printIrrelevantStations(res);
}


void restorePipes(Graph &g, const map<pair<string,string>,double>& capacities)
{
    for(pair<pair<string,string>,double> pipeInfo : capacities)
    {
        Pipe* pipe = g.findPipe(pipeInfo.first.first,pipeInfo.first.second);
        if (pipe != nullptr)
            pipe->setCapacity(pipeInfo.second);
    }
}
Pipe* getPipeInput(Graph& g)
{
    string origin,dest;
    Pipe* removed = nullptr;
    while (removed == nullptr) {
        std::cout << "Pipe origin to be removed:";
        cin >> origin;
        std::cout << "Pipe destination to be removed:";
        cin >> dest;
        removed = g.findPipe(origin,dest);
        if (removed == nullptr){
            cout << "No pipe conects those nodes\n";
        }
    }
    return removed;
}
void remPipe(Graph& g)
{
    map<pair<string,string>,double> pipesCapacities;
    FlowNetworkEvaluation(g);

    vector<pair<City*, double>> previous_city_in_deficit = getCitiesInDeficit(g);
    Pipe* pipe;
    bool finished = false;
    string option;

    while(!finished)
    {
        pipe = getPipeInput(g);

        if (pipe->getFlow()==0){
            cout<<"That Pipe removal doesn't affect performance\n";
        }else{
            pipesCapacities[{pipe->getOrig()->get_code(),pipe->getDest()->get_code()}] = pipe->getCapacity();
            pipe->setCapacity(0);

            FlowNetworkEvaluation(g);
            vector<pair<City*, double>> new_city_in_deficit = getCitiesInDeficit(g);

            printDifferences(previous_city_in_deficit, new_city_in_deficit);
            previous_city_in_deficit = new_city_in_deficit;
            cout<<"Do you want to remove another pipe?[Y/n]:";
            cin>>option;
            if (option != "Y") finished = true;
        }
    }
    restorePipes(g, pipesCapacities);
}

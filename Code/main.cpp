#include <iostream>
#include "project/Graph/Graph.h"
#include "FlowNetwork.h"
#include "reliability.h"

using namespace std;

void read_cities (Graph &graph)
{
    ifstream ifile("../project/Graph/DataSet/simple/Cities.csv");
    string line;
    string singleElement;
    if (ifile.is_open())
    {
        getline(ifile,line);
        while (getline(ifile,line))
        {
            istringstream stringline(line);
            string name; getline(stringline,name,',');
            int id; getline(stringline,singleElement,',');
            id = stoi(singleElement);
            string code; getline(stringline,code,',');
            int demand; getline(stringline,singleElement,','); demand = stoi(singleElement);
            int population; getline(stringline,singleElement,','); population = stoi(singleElement);
            City newcity = City(id,code,name,demand,population);

            graph.addCity(id,code,name,demand,population);
            graph.cityToCode[name] = code;
        }
    }
}
void read_reservoirs (Graph &graph)
{
    ifstream ifile("../project/Graph/DataSet/simple/Reservoir.csv");
    string line;
    if (ifile.is_open())
    {
        string singleElement;
        getline(ifile,line);
        while (getline(ifile,line))
        {
            istringstream stringline(line);
            string name; getline(stringline,name,',');
            string municipality; getline(stringline, municipality,',');
            int id; getline(stringline,singleElement,','); id = stoi(singleElement);
            string code; getline(stringline,code,',');
            int maximum; getline(stringline,singleElement,','); maximum = stoi(singleElement);
            Reservoir reservoir = Reservoir(id,code,name,municipality,maximum);

            graph.addReservoir(id,code,name,municipality,maximum);
        }
    }
}
void read_stations (Graph &graph)
{
    ifstream ifile("../project/Graph/DataSet/simple/Stations.csv");
    string line;
    if (ifile.is_open())
    {
        string singleElement;
        getline(ifile,line);
        while (getline(ifile,line))
        {
            istringstream stringline(line);
            int id; getline(stringline,singleElement,','); id = stoi(singleElement);
            string code; getline(stringline,code,',');
            Station station = Station(id,code);

            graph.addStation(id,code);
        }
    }
}
void read_pipes(Graph &graph)
{
    ifstream ifile("../project/Graph/DataSet/simple/Pipes.csv");
    string line;
    if (ifile.is_open())
    {
        string singleElement;
        getline(ifile,line);
        while (getline(ifile,line))
        {
            istringstream stringline(line);
            string pointA; getline(stringline,pointA,',');
            string pointB; getline(stringline,pointB,',');
            double capacity;
            getline(stringline,singleElement,',');
            capacity = stoi(singleElement);
            int direction; getline(stringline,singleElement,','); direction = stoi(singleElement);

            if (direction == 0)
            {
                if (! graph.addBidirectionalPipe(pointA,pointB,capacity))
                    exit(EXIT_FAILURE);
            }else{
                if (! graph.addPipe(pointA,pointB,capacity))
                    exit(EXIT_FAILURE);
            }
        }
    }
}

int main() {
    Graph g;
    read_cities(g);
    read_stations(g);
    read_reservoirs(g);
    read_pipes(g);
    std::cout << "Bem-vindo!" << std::endl;

    //FlowNetworkEvaluation(g);
    //vector<pair<City*, double>> cities = getCitiesInDeficit(g);
    //PrintResults(cities);
    remStation(g);
    remStation(g);

    return 0;
}

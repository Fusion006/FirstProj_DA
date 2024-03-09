#include "Graph.h"


using namespace std;

void read_cities (map<int,City>& cities, map<string,int>& nameToId)
{
    ifstream ifile("../project/Graph/DataSet/Cities.csv");
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
            cities.insert({id,newcity});
            nameToId.insert({name,id});
        }
    }
}
void read_reservoirs (map<int,Reservoir>& reservoirs)
{
    ifstream ifile("../project/Graph/DataSet/Reservoir.csv");
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
            reservoirs.insert({id,reservoir});
        }
    }
}
void read_stations (map<int,Station>& stations)
{
    ifstream ifile("../project/Graph/DataSet/Stations.csv");
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
            stations.insert({id,station});
        }
    }
}

Graph::Graph()
{
    read_cities(this->cities, this->nameToId);
    read_reservoirs(this->reservoirs);
    read_stations(this->stations);
}


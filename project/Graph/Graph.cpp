#include "Graph.h"


using namespace std;

void read_cities (map<string ,City*>& cities, map<string,string>& nameToCode)
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

            cities.insert({code,&newcity});
            nameToCode.insert({name,code});
        }
    }
    int a;
}
void read_reservoirs (map<string ,Reservoir*>& reservoirs, map<string,string>& nameToCode)
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

            reservoirs.insert({code,&reservoir});
            nameToCode.insert({name,code});
        }
    }
}
void read_stations (map<string ,Station*>& stations)
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

            stations.insert({code,&station});
        }
    }
    int test;
}

void read_pipes(map<string ,City*>& cities, map<string ,Reservoir*>& reservoirs, map<string ,Station*>& stations)
{
    ifstream ifile("../project/Graph/DataSet/Pipes.csv");
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
            int capacity;
            getline(stringline,singleElement,',');
            capacity = stoi(singleElement);
            int direction; getline(stringline,singleElement,','); direction = stoi(singleElement);

            Vertex* source;
            Vertex* dest;

            if (pointA[0] == 'P')      source = stations[pointA];
            else if (pointA[0] == 'R') source = reservoirs[pointA];
            else if (pointA[0] == 'C') source = cities[pointA];

            if (pointB[0] == 'P')      dest = stations[pointB];
            else if (pointB[0] == 'R') dest = reservoirs[pointB];
            else if (pointB[0] == 'C') dest = cities[pointB];

            Pipe* newPipe = new Pipe(source,dest,capacity);
            source->add_pipe(newPipe);

            if (direction == 0)
            {
                newPipe = new Pipe(source,dest,capacity);
                dest->add_pipe(newPipe);
            }
        }
    }
}

Graph::Graph()
{
    read_cities(this->cities, this->nameToCode);
    read_reservoirs(this->reservoirs, this->nameToCode);
    read_stations(this->stations);
    int a;
    read_pipes(this->cities, this->reservoirs, this->stations);
}


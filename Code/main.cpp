#include <iostream>
#include "project/Graph/Graph.h"
#include "FlowNetwork.h"
#include "rebalance.h"
#include "reliability.h"
#include "optimalflow.h"

using namespace std;


/** Function to read and parse the graph's cities info.
 *  Creates in the graph the vertexes that contain the information of the cities.
 * @param graph graph that will receive the new nodes.
 * @param cities path where it is located the file that has the info.
 */
void read_cities (Graph &graph, string& cities)
{
    ifstream ifile(cities);
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
/** Function to read and parse the graph's reservoirs info.
 *  Creates in the graph the vertexes that contain the information of the reservoirs.
 * @param graph graph that will receive the new nodes.
 * @param reservoirs path where it is located the file that has the info.
 */
void read_reservoirs (Graph &graph, string& reservoirs)
{
    ifstream ifile(reservoirs);
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
/** Function to read and parse the graph's pumping stations info.
 *  Creates in the graph the vertexes that contain the information about these stations.
 * @param graph graph that will receive the new nodes.
 * @param stations path where it is located the file that has the info.
 */
void read_stations (Graph &graph, string& stations)
{
    ifstream ifile(stations);
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
/** Function to read and parse the graph's pipeline info.
 *  Creates in the graph the edges (pipelines) that contain the information about these pipes.
 * @param graph graph that will receive the new nodes.
 * @param pipes path where it is located the file that has the info.
 */
void read_pipes(Graph &graph, string& pipes)
{
    ifstream ifile(pipes);
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
/** Function that takes care of the User Interface.
 *  This function receives the user's orders and answers them according to the user's wish.
 * @param graph graph to give as an argument to the functions that actually respond to the user tasks.
 */
void run(Graph& graph) {
    string order;
    while (true) {
        cout << endl << "What do you wish to do?" << endl << endl <<
             "Please insert:" << endl <<
             "'1' to see the maximum amount of water that can reach each or a specific city;" << endl <<
             "'2' to see if all the water reservoirs are able to supply enough water to all the cities in need;" << endl <<
             "'3' to try to balance the flow that goes trough the network;" << endl <<
             "'4' to simulate the malfunctioning of one or more Reservoirs and its consequences;" << endl <<
             "'5' to see see what would happen if one or more Pumping Stations are removed;" << endl <<
             "'6' to find out if one or more Pipelines are crucial to the good functioning of the water delivery;" << endl <<
             "'close' to exit the program." << endl;
        getline(cin >> ws, order);

        if (order == "close") {
            cout << "Closing now..." << endl;
            return;
        }

        else if (order == "1") {
            Opt_Flow(graph);
        }

        else if (order == "2") {
            FlowNetworkEvaluation(graph);
            auto vec = getCitiesInDeficit(graph);
            PrintResults(vec);
        }

        else if (order == "3") {
            FlowBalance(graph);
        }

        else if (order == "4") {
            remReservoir(graph);
        }

        else if (order == "5") {
            remStation(graph);
        }

        else if (order == "6") {
            remPipe(graph);
        }

        else cout << "Insert a valid number!" << endl;
    }
}

int main() {
    Graph g;
    string dataSet;
    string resPath,cityPath,stationPath,pipePath;
    std::cout << "Welcome!" << std::endl;

    while (dataSet.empty()){
        cout << "Which Dataset do you want to use[Big/Small/Custom]:" << endl;
        getline(cin >> ws, dataSet);

        if (dataSet == "Big"){
            resPath     =   "../project/Graph/DataSet/Reservoir.csv";
            cityPath    =   "../project/Graph/DataSet/Cities.csv";
            stationPath =   "../project/Graph/DataSet/Stations.csv";
            pipePath    =   "../project/Graph/DataSet/Pipes.csv";
        }

        else if (dataSet == "Small"){
            resPath     =   "../project/Graph/DataSet/Reservoirs_Madeira.csv";
            cityPath    =   "../project/Graph/DataSet/Cities_Madeira.csv";
            stationPath =   "../project/Graph/DataSet/Stations_Madeira.csv";
            pipePath    =   "../project/Graph/DataSet/Pipes_Madeira.csv";
        }

        else if (dataSet == "Custom") {
            cout << "Please insert the path to the file that contains the Cities information:" << endl;  //  ../project/Graph/DataSet/Cities.csv
            getline(cin >> ws, cityPath);

            cout << "Please insert the path to the file that contains the Pumping Stations information:" << endl;  //  ../project/Graph/DataSet/Stations.csv
            getline(cin >> ws, stationPath);

            cout << "Please insert the path to the file that contains the Reservoirs information:" << endl;  //  ../project/Graph/DataSet/Reservoir.csv
            getline(cin >> ws, resPath);

            cout << "Please insert the path to the file that contains the Pipelines information:" << endl;  //  ../project/Graph/DataSet/Pipes.csv
            getline(cin >> ws, pipePath);
        }

        else {
            dataSet="";
        }
    }

    read_cities(g,cityPath);
    read_stations(g,stationPath);
    read_reservoirs(g,resPath);
    read_pipes(g,pipePath);

    run(g);

    return 0;
}

#include "optimalflow.h"

using namespace std;


double getTotalFlow(City* city) {
    double sum = 0;
    for (auto pipe : city->getIncoming()) {
        sum += pipe->getFlow();
    }
    return sum;
}

void Opt_Flow(Graph& graph) {
    FlowNetworkEvaluation(graph);
    string order;
    vector<pair<City *, double>> v;
    v.clear();
    while (order != "back") {

        cout << endl << "Please insert:" << endl <<
             "'1' to see the maximum amount of water that can reach a specific city;" << endl <<
             "'2' to see the maximum amount of water that can reach each city;" << endl <<
             "'back' to get back to the main menu." << endl;

        getline(cin >> ws, order);
        if (order == "1") {

            cout << "Insert the code of the city:" << endl;
            string cityCode;
            getline(cin >> ws, cityCode);
            auto city = graph.findCity(cityCode);

            if (city == nullptr) {
                cout << "Insert a valid City code!" << endl;
                continue;
            }

            cout << "The maximum flow for the city of " << city->get_name() << " of code " << city->get_code() << " is " << getTotalFlow(city) << endl;
        }

        else if (order == "2") {
            if (v.empty()) {
                for (auto city : graph.getCities()) {
                    v.emplace_back(city, getTotalFlow(city));
                }
            }
            Opt_printResult(v);

        } else {
            cout << "Insert a valid number!" << endl;
        }
    }
}

void Opt_printResult(vector<pair<City*, double>>& vec){
    std::sort(vec.begin(), vec.end(), sortCitiesByDeficit);

    for(auto& pair : vec){
        cout << "The maximum flow for " << pair.first->get_name() << " of code " << pair.first->get_code() << " is " << pair.second << endl;
    }
}

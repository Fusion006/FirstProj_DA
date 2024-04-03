#include "rebalance.h"

using namespace std;



vector<vector<string>> bfsRebalance(const string & source, Graph& graph) {
    std::vector<string> vec;
    vector<vector<string>> res;
    // Get the source vertex
    auto s = graph.findVertex(source);
    if (s == nullptr) {
        return res;
    }

    // Set that no vertex has been visited yet
    for (auto v: graph.getVertexSet()) {
        v->setVisited(false);
    }

    // Perform the actual BFS using a queue
    std::queue<Vertex *> q;
    q.push(s);
    s->setVisited(true);
    s->setDist(0);
    double distance = 0;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if (v->getDist() > distance) {
            res.push_back(vec);
            vec.clear();
            distance += 1;
        }
        if (v->getDist() != 0 && v->get_code() != "SuperC")
        vec.push_back(v->get_code());
        for (auto &e: v->getAdj()) {
            auto w = e->getDest();
            w->setDist(v->getDist()+1);
            if (!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

double getMedian(Graph& graph) {
    vector<double> diferences;
    for (Vertex* v : graph.getVertexSet()) {
        for (Pipe* pipe : v->getAdj()) {
            diferences.push_back(pipe->getCapacity() - pipe->getFlow());
        }
    }
    std::sort(diferences.begin(), diferences.end());
    if (diferences.size() % 2 != 0) {
        return diferences.at(diferences.size()/2);
    }
    else {
        return (diferences.at(diferences.size()/2) + diferences.at(diferences.size()/2 -1)) / 2;
    }
}

double getVertexMedian(const string& code, Graph& graph) {
    Vertex* vertex = graph.findVertex(code);
    vector<double> diferences;
    for (Pipe* pipe : vertex->getAdj()) {
        diferences.push_back(pipe->getCapacity() - pipe->getFlow());
    }

    if (diferences.empty()) return 0;

    std::sort(diferences.begin(), diferences.end());
    if (diferences.size() % 2 != 0) {
        return diferences.at(diferences.size()/2);
    }
    else {
        return (diferences.at(diferences.size()/2) + diferences.at(diferences.size()/2 -1)) / 2;
    }
}

int getNumberOfUnusedPipes(Graph& graph) {
    int res = 0;
    for (Vertex* v : graph.getVertexSet()) {
        for (Pipe* pipe : v->getAdj()) {
            if (pipe->getFlow() == 0) res++;
        }
    }
    return res;
}

vector<pair<string, pair<string, double>>> getOriginalCapacities(Graph& graph) {
    vector<pair<string, pair<string, double>>> res;
    for (Vertex* v : graph.getVertexSet()) {
        for (Pipe* pipe : v->getAdj()) {
            res.emplace_back(pipe->getOrig()->get_code(), make_pair(pipe->getDest()->get_code(), pipe->getCapacity()));
        }
    }
    return res;
}

void FlowBalance(Graph& graph) {
    FlowNetworkEvaluation(graph);
    int numberOfUnusedPipes = getNumberOfUnusedPipes(graph);
    int oldNumber = 0;
    double median = 0;
    vector<pair<string, pair<string, double>>> origin = getOriginalCapacities(graph);
    CreateSuperSourceSink(graph);
    auto vec = bfsRebalance("SuperR", graph);
    DestroySuperSourceSink(graph);

    for (const auto& vecDist : vec) {
        for (const string& string1 : vecDist) {
            Vertex* v = graph.findVertex(string1);
            median = getVertexMedian(v->get_code(), graph);
            if (median == 0) continue;
            for (Pipe* pipe : v->getAdj()) {
                if (pipe->getCapacity() == pipe->getFlow() && pipe->getCapacity() > median) {
                    pipe->setCapacity(pipe->getCapacity()-median);
                }
            }
            FlowNetworkEvaluation(graph);
        }
    }
    oldNumber = numberOfUnusedPipes;
    numberOfUnusedPipes = getNumberOfUnusedPipes(graph);
    cout << "old:   " << oldNumber << "      " << "new:   " << numberOfUnusedPipes << endl;
    /*
    while (true) {
        for (Vertex* v : graph.getVertexSet()) {
            median = getVertexMedian(v->get_code(), graph);
            if (median == 0) continue;
            for (Pipe* pipe : v->getAdj()) {
                if (pipe->getCapacity() == pipe->getFlow() && pipe->getCapacity() > median) {
                    pipe->setCapacity(pipe->getCapacity()-median);
                }
            }
            FlowNetworkEvaluation(graph);
        }
        oldNumber = numberOfUnusedPipes;
        numberOfUnusedPipes = getNumberOfUnusedPipes(graph);
        cout << "old:   " << oldNumber << "      " << "new:   " << numberOfUnusedPipes << endl;
        if (numberOfUnusedPipes == 0 || numberOfUnusedPipes >= oldNumber) {
            break;
        }
    }
     */
    for (const auto& pair : origin) {
        Pipe* pipe = graph.findPipe(pair.first, pair.second.first);
        pipe->setCapacity(pair.second.second);
    }
}

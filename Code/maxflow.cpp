#include "maxflow.h"

using namespace std;


bool shortestPath(Graph &g, string &source, string &target, vector<string> *v){
    v->clear();
    auto s = g.findVertex(source);
    auto t = g.findVertex(target);
    if( s == nullptr || t == nullptr) return false;
    for(Vertex* v1 : g.getVertexSet()){
        v1->setVisited(false);
        v1->setPath(nullptr);
    }
    queue<Vertex*> que;
    que.push(s);
    s->setVisited(true);
    while(!que.empty()){
        Vertex* vert = que.front();
        que.pop();
        for(Pipe* pp : vert->getAdj()){
            if(pp->getCapacity() == 0) continue;
            Vertex* w = pp->getDest();
            if(!w->isVisited()){
                w->setPath(pp);
                que.push(w);
                w->setVisited(true);
            }
        }
    }
    if(!t->isVisited()) return false;
    Pipe* pp2 = t->getPath();
    while(pp2->getOrig()->get_code() != s->get_code()){
        v->insert(v->begin(), pp2->getDest()->get_code());
        pp2 = pp2->getOrig()->getPath();
    }
    v->insert(v->begin(), pp2->getDest()->get_code());
    return true;
}

void edmondsKarp(Graph &g, string &source, string &target){
    for(Vertex* v : g.getVertexSet()){
        for(Pipe* pp : v->getAdj()){
            pp->setSelected(true);
            pp->setFlow(0);
        }
    }
    Graph g1;
    for(Vertex* vt : g.getVertexSet()) g1.addVertex(vt->get_id(), vt->get_code());
    for(Vertex* vt : g.getVertexSet()){
        for(Pipe* pp : vt->getAdj()) g1.addPipe(pp->getOrig()->get_code(), pp->getDest()->get_code(), pp->getCapacity());
    }
    for(Vertex* vt : g1.getVertexSet()){
        for(Pipe* pp : vt->getAdj()){
            pp->setSelected(true);
            pp->setFlow(0);
        }
    }
    vector<string> shortest_path;
    vector<string>* shortest_pointer = &shortest_path;
    while(shortestPath(g1, source, target, shortest_pointer)){
        double minCapacity = INT_MAX;
        Vertex* vt = g1.findVertex(source);
        for(const string& v : *shortest_pointer){
            vt = g1.findVertex(v);
            if(vt->getPath()->getCapacity() < minCapacity) minCapacity = vt->getPath()->getCapacity();
        }
        for(const string& v : *shortest_pointer){
            vt = g1.findVertex(v);
            Pipe* path = vt->getPath();
            if(path->isSelected()) {
                path->setFlow(path->getFlow() + minCapacity);
                path->setCapacity(path->getCapacity() - minCapacity);
                if (path->getReverse() == nullptr) {
                    Pipe *rev = path->getDest()->addPipe(path->getOrig(), 0);
                    path->setReverse(rev);
                    rev->setReverse(path);
                    rev->setSelected(false);
                }
                path->getReverse()->setCapacity(path->getReverse()->getCapacity() + minCapacity);
                path->getReverse()->setFlow(path->getFlow());
            }
            else{
                path->setFlow(path->getFlow() - minCapacity);
                path->setCapacity(path->getCapacity() - minCapacity);
                path->getReverse()->setCapacity(path->getReverse()->getCapacity() + minCapacity);
                path->getReverse()->setFlow(path->getFlow());
            }
        }
    }
    for(Vertex* v : g1.getVertexSet()){
        for(Pipe* pp : v->getAdj()){
            if(pp->getReverse() != nullptr){
                pp->setCapacity(pp->getCapacity() + pp->getReverse()->getCapacity());
                pp->setReverse(nullptr);
                pp->getDest()->removePipe(pp->getOrig()->get_code());
            }
        }
    }
    for (Vertex* v : g1.getVertexSet()) {
        for(Pipe* pipe : v->getAdj()){
            Pipe* pipe1 = g.findPipe(pipe->getOrig()->get_code(), pipe->getDest()->get_code());
            if (pipe1 != nullptr) {
                pipe1->setFlow(pipe->getFlow());
            }
        }
    }
    
}
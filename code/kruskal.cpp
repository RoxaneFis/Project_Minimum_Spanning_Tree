
#include <iostream>
#include <cmath>
#include <cassert>

#include "kruskal.hpp"
//#include "boostgraph.hpp"


kruskal::kruskal( boostgraph& _g)
{
    di=_g.di;
    V=_g.V;
    occurences = _g.occurences;
    vectors=_g.vectors;

    // A. INITALISATION
    count=0;
    unionfind *u = new unionfind();
    u->SetUp(_g);
    edge e;
    std::list<edge>* edges=&_g.edges;
    edges->sort();
    edges->reverse();

    // B. BOUCLE
    std::list<edge>::iterator it;
    for (it = (*edges).begin(); it != (*edges).end(); ++it) {
        e=*(it);
        if(u->trouver(*e.start).numero!=u->trouver(*e.finish).numero){
            MST.push_back(e);
            count=count+e.poids;
            u->uni(*e.start,*e.finish);
        }
    }
}



void kruskal::addAllSetEdge(std::set<edge> q,   std::set<edge> liste ){
    std::set<edge>::iterator it2;
    for (it2 = liste.begin(); it2 != liste.end(); ++it2) {
        edge e=*it2;
        q.insert(e);
    }

}

kruskal::~kruskal(){

}

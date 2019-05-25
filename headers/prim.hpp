#ifndef PRIM_H
#define PRIM_H
#include "boostgraph.hpp"
#include <unordered_set>
#include <queue>
#include <map>

class Prim
{
public:
    //Parametres
    std::list<edge>  MST;
    double count;


    //constructeurs
    Prim(node& _start,boostgraph& _g);


    //Fonction
    void addAllqueueEdge(std::priority_queue<edge> &q,   std::list<edge> liste);
    void addAllqueueEdge(std::priority_queue<edge> &q,   std::list<edge> liste, edge& p );



};

#endif // PRIM_H

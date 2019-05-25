#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "boostgraph.hpp"
#include "unionfind.hpp"


class kruskal
{
public:
    kruskal(boostgraph& _g);
    ~kruskal();
    kruskal( boostgraph& _g, unionfind& u);
    std::list<edge>  MST;
    int V;
    std::vector<item> vectors;
    dist*di;
    std::map<std::string,int > occurences ;

    double count;



    //fonction
    void addAllSetEdge(std::set<edge> q,   std::set<edge> liste );


};

#endif // KRUSKAL_H

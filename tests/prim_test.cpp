

#include <iostream>
#include <cmath>
#include <cassert>

/*#include "boostgraph.hpp"
#include "prim.hpp"*/
#include "boostgraph.cpp"
#include "prim.cpp"



int main(int argc,  char *argv[])
{
    //CONSTRUCTION GRAPH
    dist * d = new Eucli();
    boostgraph *graph;
    graph=new boostgraph(argv[1],*d);
    Prim *j;
    std::set<node>::iterator it = graph->nodes.begin();
    node start = *it;

    //CONSTRUCTION MST-PRIM
    j = new Prim(start, *graph);
    graph->printEdges(j->MST);
    std::cout<<"SOMME TOTALE: "<<j->count<<std::endl;

    return 0;


}


#include <iostream>
#include <cmath>
#include <cassert>
#include "kruskal.cpp"
#include "boostgraph.cpp"
#include "unionfind.cpp"


int main(int argc,  char *argv[])
{
    //CREATION DU GRAPH
    boostgraph *graph;
    dist * d= new Eucli();
    graph=new boostgraph(argv[1],*d);

    //CREATION DE KRUSKAL
    kruskal *j;
    j = new kruskal(*graph);
    graph->printEdges(j->MST);
    std::cout<<"SOMME TOTALE : "<<j->count<<std::endl;


    return 0;


}



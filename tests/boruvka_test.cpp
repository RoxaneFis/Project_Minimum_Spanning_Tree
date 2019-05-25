#include <iostream>
#include <cmath>
#include <cassert>

#include "boostgraph.cpp"
#include "unionfind.cpp"
#include "boruvka.cpp"



int main(int argc,  char *argv[])
{
    //CREATION GRAPH
    boostgraph *graph;

   // dist * d = new Eucli();
    graph=new boostgraph(argv[1]);

     //CREATION BORUVKA
    std::cout<<std::endl;
    std::cout<<"Boruvka Test "<<std::endl;
    boruvka *j;
    j = new boruvka(*graph);
    graph->printEdges(j->MST);
    std::cout<<"count: "<<j->count<<std::endl;
    std::cout<<std::endl;
    return 0;

}

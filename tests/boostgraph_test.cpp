#include <iostream>
#include <cmath>
#include <cassert>


#include "boostgraph.cpp"




int main(int argc,  char *argv[])
{

    boostgraph *graph;
    dist * d = new Eucli();
    graph=new boostgraph(argv[1],*d);
    graph->printGraph();
    return 0;

}
//hello

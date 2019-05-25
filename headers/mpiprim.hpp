#ifndef MPIPRIM_H
#define MPIPRIM_H
#include "boostgraph.hpp"
#include <mpi.h>



class mpiprim
{
public:
    //Parametres
    double  **tab;
    
    //constructeurs
    mpiprim(boostgraph& _g, int numtasks, int taskid);
    void static graphconstruct(double** graph,boostgraph& _g);
    int static printGraph(double** graph, int V);
    int printMST(int pred[], double** graph, int V);
};

#endif // PRIM_H


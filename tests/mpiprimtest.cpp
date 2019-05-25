#include <iostream>
#include "boostgraph.cpp"
#include "mpiprim.cpp"
#include <stdio.h>
#include <mpi.h>



int main(int argc, char *argv[])
{
    boostgraph *g;
    g = new boostgraph("dataproduced5.txt");
    
    int name_len;
    int numtasks, taskid;
    
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    
    clock_t start;
    double duration;
    start = clock();
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    

    mpiprim*j;
    j = new mpiprim(*g,numtasks,taskid);
        
    MPI_Finalize();
    
    
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"Temps d'execution : "<< duration <<'\n';

    return 0;
}



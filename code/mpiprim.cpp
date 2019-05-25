#include "mpiprim.hpp"
#include "boostgraph.hpp"


//indices always go from 1 to V+1 because vertices' names go from 1 to V

//create an array storing graph _g from constrcutor boostgraph used since beginning of project
void mpiprim::graphconstruct(double **graph,boostgraph& _g){
    std::list<edge>::iterator it;
    
    for (it = (_g.edges).begin(); it != (_g.edges).end(); ++it) {
        struct edge e = *it;
        int i = e.start->numero;
        int j = e.finish->numero;
        graph[i-1][j-1] = e.poids;
        graph[j-1][i-1] = e.poids;
    }
}

//print graph
int mpiprim::printGraph(double** graph, int V){
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j ++){
            std::cout<< " " << graph[i][j] << "|";
        }
        std::cout<<""<<endl;
    }
    std::cout<<"----fin du print graph"<<endl;

    return 1;
}

//print MST
int mpiprim::printMST(int pred[], double** graph, int V){
    cout<<"Edge - Weight"<< endl;
    for (int i = 1; i < V; i++)
        if(pred[i]>=0){
            cout<<pred[i]+1<<" - "<<i+1<<"    "<<graph[i][pred[i]]<<endl;
        }
    return 1;
}

//compute MST from graph _g
mpiprim::mpiprim(boostgraph& _g, int numtasks, int taskid)
{
    //std::cout<<"numtasks vaut "<<numtasks<<endl;
    //std::cout<<"taskid vaut "<<taskid<<endl;
    int V = _g.V;
    
    tab = new double*[V];
    for(int i = 0; i < V; ++i) {
        tab[i] = new double[V];
    }
    
    //initialisation du tableau tab
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j ++){
            tab[i][j]=0.0;
        }
    }
            
            
    graphconstruct(tab,_g);
    int pred[V]; // array containing vertices choosen succesively
    int minweight[V];   // array containing the weigth of the mininmum outgoing edge for each vertex
    int isInMST[V];  // equals 1 if vertex has been added to mst, 0 otherwise
    
    
    const int root = 0;
    
    // we add vertex number 0
    minweight[0] = INT_MAX;
    pred[0] = -1; // it does not have any predecessor
    isInMST[0] = 1;
    
    
    MPI_Status stat;
    MPI_Request request = MPI_REQUEST_NULL;
    
    
    //INITIALIZATION
    for (unsigned int v = 1; v < V; v++){
        if (tab[0][v] > 0){
            isInMST[v] = 0, pred[v] = 0, minweight[v] = tab[0][v];
        }
        else {
            isInMST[v] = 0, pred[v] = 0, minweight[v] = INT_MAX;
        }
    }
    
    
    // we complete the array pred
    for (unsigned int i = 1; i < V - 1; i++)
    {
        
        int local_u = 0;
        int local_min = INT_MAX;
        
        // each core take care of its vertices to find their minimum outgoing edge
        for (int v = taskid; v < V; v+=numtasks){
            if (isInMST[v] == 0 && minweight[v] < local_min){
                local_min = minweight[v], local_u = v;
            }
        }
        
        MPI_Send(&local_u,1,MPI_INT,root,0,MPI_COMM_WORLD);
        
        int u_min = 0;
        int u = 0;
        
        if (taskid == root){
            int min = INT_MAX;
            for (int p = 0; p < numtasks; p++){
                // root receive local minima et choose the right candidate
                MPI_Recv(&u,1,MPI_INT,p,0,MPI_COMM_WORLD,&stat);
                if (minweight[u] < min){
                    min = minweight[u], u_min = u;
                }
            }
            // Iwe mark the vertex as added in the MST
            isInMST[u_min] = 1;
        }
        
        MPI_Bcast(&u_min, 1, MPI_INT, root, MPI_COMM_WORLD);
        MPI_Bcast(&isInMST, V, MPI_INT, root, MPI_COMM_WORLD);
        
        
        
        // Update of pred by each core
        // Update of vertices minweight that are not yet in MST
        for (unsigned int v = taskid; v < V; v+=numtasks){
            if (tab[u_min][v] > 0 && isInMST[v] == 0 && tab[u_min][v] <  minweight[v] && v > 0){
                pred[v] = u_min, minweight[v] = tab[u_min][v];
            }
        }
        
        // we send updated minweight and pred arrays to root
        MPI_Send(&minweight,V,MPI_INT,root,2,MPI_COMM_WORLD);
        MPI_Send(&pred,V,MPI_INT,root,2,MPI_COMM_WORLD);
        
        if (taskid == 0){
            int tmp_minweight[V];
            int tmp_pred[V];
            for (int p = 0; p < numtasks; p++){
                MPI_Recv(&tmp_minweight,V,MPI_INT,p,2,MPI_COMM_WORLD,&stat);
                MPI_Recv(&tmp_pred,V,MPI_INT,p,2,MPI_COMM_WORLD,&stat);
                for (int j = p ; j < V ; j+=numtasks){
                    minweight[j] = tmp_minweight[j];
                    pred[j] = tmp_pred[j];
                }
            }
        }
        //we broadcast the new pred and cost array unified
        MPI_Bcast(&pred, V, MPI_INT, root, MPI_COMM_WORLD);
        MPI_Bcast(&minweight, V, MPI_INT, root, MPI_COMM_WORLD);
        
        MPI_Wait(&request,&stat);
    }
    
    // we print the MST
    if (taskid==0)
        printMST(pred,tab,V);
}

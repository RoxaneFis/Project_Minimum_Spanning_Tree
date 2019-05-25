
#include "k_clusters.cpp"
#include "boostgraph.cpp"


int main(int argc,  char *argv[]){

    //CONSTRUCTION GRAPH
    boostgraph *graph;
    dist* d = new Inf();
    graph=new boostgraph(argv[1],*d);
   // boostgraph::printEdges(graph->edges);

    //CONSTRUCTION KRSUKAL
    kruskal *j;
    j = new kruskal(*graph);


    //CONSTRUCTION CLUSTERS : 1 à N

    for(int k=9;k<10;k++){
        kclusters *clu ;
        clu=new kclusters( *j,k);
        clu->setBarycentres();
        //std::cout<<"-----------BOUCLE K="<<k<<"  -------------------------------------------"<<std::endl;
       clu->printBary();
        clu->print();
       // std::cout<<clu->intraclusters()/clu->interclusters()<<std::endl;
    }
    return 0;
}

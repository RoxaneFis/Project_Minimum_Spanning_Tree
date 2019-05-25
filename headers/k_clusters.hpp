#ifndef KCLUSTERS_HPP
#define KCLUSTERS_HPP
#include <iostream>
#include <list>
#include <map>


#include "kruskal.hpp"

class kclusters
{
public:
    ~kclusters();
    kclusters( kruskal j,int k);



    dist*di;
    int _k;

    //TRAITEMENT MST

    std::list<edge>  Tprime; //MST avec des arrêtes supprimés
    std::set<edge> reduced; //Arrêtes supprimées
    std::set<node>  isoles; //Noeuds seuls dans leur cluster
     int nb_clusters_reel;  //Nb de clusters à plus d'un élément

    //CLUSTERS
    std::map<int,std::set<node> >  clusters; //Map des Clusters
    std::map<int,std::string> correspondance; //Association numero/nom
    std::vector<item> vectors; //Item associé à chaque noeud i
    int * marque; //Numéro de Cluster associé à chaque noeud i


    //BARYCENTRES
    item * barycentres;  //Tableau Barycentres (nb_clusters_reel items)
    item barycentre; //Barycentre total


    double error();
    double true_error();

    void setBarycentres();
    double intraclusters();
    double interclusters();
    double intraclusters_simple();
    double interclusters_simple();

    void print();
    void printNode(std::set<node> q);
    void printBary();


};

#endif // KCLUSTERS_HPP

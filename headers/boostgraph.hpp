#ifndef BOOSTGRAPH_H
#define BOOSTGRAPH_H

//#include <QApplication>
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <sstream>
#include <queue>
#include <fstream>
#include<map>
#include<queue>
#include<set>
#include "dist.cpp"

//------------STRUCTURES NOEUDS/ARRETES--------------------

struct node{
    int numero;
    int cluster;
    std::string name;

    //opérateurs
    bool operator<(const node& rhs) const
    {return numero<rhs.numero; }
    bool operator>(const node& rhs) const
    {return numero>rhs.numero;}

};

struct edge{
    node * start;
    node * finish;
    double poids;
    void print(){
        std::cout<<start->numero<<" - "<<finish->numero<<" /Poids : "<<poids<< std::endl; }
    bool operator<(const edge& rhs) const {
        if(poids==rhs.poids){
            if(start->numero>rhs.start->numero){
                return start->numero>rhs.start->numero;
            }
            else{
                return finish->numero>rhs.finish->numero;
            }
        }
        return poids>rhs.poids;}

    bool operator==(const edge& rhs) const{
        return ((poids)==(rhs.poids) && start==rhs.start && finish==rhs.finish);
    }
};




class boostgraph
{
public:

    //PARAMETRES
    int V;
    int nbEdges;
    dist *di ;
    std::map < node,std::list <edge> > voisins; //Map de noeuds et de leurs arretes sortantes
    std::set<node> nodes; //Ensemble des Noeuds
    std::list<edge> edges; // Ensemble des Arretes
    std::vector<item> vectors; //Prétraitement des noeuds (initialement vecteurs de R^^D)
    std::map<std::string,int > occurences ; // Partie Clustering : Occurences de chaque catégorie (Iris,Rose...)

    //CONSTRUCTEURS
    boostgraph(std::string file,dist& d); //Graph complet à partir d'un fichier de vecteurs
    boostgraph(std::string file); //Graph non complet à partir d'un fichier d'arrêtes
    boostgraph();

    //FONCTIONS
    node *newnode(int,std::string nom);
    edge *newedge(node* i, node* j,double w);
    std::vector<std::string> split(std::string str, char delimiter); //pour lire un fichier (separer mots dans une ligne)

    //PRINT
    void printGraph();
    static void printNode(std::vector<node*> q);
    static void printNode(std::set<node> q);
    static void printEdges(std::list<edge> q);
    static void printEdges(std::set<edge> q);

};

#endif // BOOSTGRAPH_H
//comentaire

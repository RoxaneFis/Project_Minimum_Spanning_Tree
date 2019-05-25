#include<iostream>
#include<cstdlib>
#include <map>
#include "boostgraph.hpp"
using namespace std;


//------------CONSTRUCTEURS--------------------

//Constructeur à partir de vecteurs :



boostgraph::boostgraph(std::string file,dist& d){
    int count=0;
    di=&d ;

    //------OUVERTURE FICHIER------------------
    std::cout<<"Loading road networks from file " << file << " ... "<<std::endl;
    std::string ligne;
    ifstream Myfile;
    Myfile.open(file);
    getline(Myfile,ligne);
    while (!(ligne[0] == '@' && ligne[1]=='d' &&ligne[2]=='a'&& ligne[3]=='t' && ligne[4]=='a')){
        getline(Myfile,ligne);}
    getline(Myfile,ligne);


    // ---------LECTURE FICHIER ---------------
    while (Myfile) {
        count=count+1;
        std::vector<std::string> sep = split(ligne, ' ' );
        int dim=sep.size();
        item *a=new item(count,dim-1);
        a->dim=dim-1;
        for (int i =0;i<dim-1;i++){
            a->coord[i] = std::stod(sep[i]);

        }
        a->name=sep[dim-1];
        vectors.push_back(*a);
        getline(Myfile,ligne);
        occurences[a->name]=occurences[a->name]+1;

    }
    Myfile.close();
    V=count;


    //--------CREATION GRAPH COMPLET---------------
    for (int i =0;i<count;i++){
        for (int j=0;j<i;j++){
            node*nodei = newnode(i+1,vectors[i].name);
            node*nodej = newnode(j+1,vectors[j].name);

            double dis =  d.calcul(vectors[i],vectors[j]);
            edge ei=*newedge(nodei,nodej,dis);


            //INSERTIONS
            nodes.insert(*nodei);
            nodes.insert(*nodej);
            edges.push_back(ei); //tous les edges

            //----------Insere Edge e a la map voisin  pour i
            map<node, std::list<edge> >::iterator iti ;
            iti=voisins.find((*nodei)) ; //ref unique de nodei dans nodes //ex : i
            if(iti!=voisins.end()){ //node i pas incore dans nodes
                iti->second.push_back(ei);
            }
            else{
                std::list<edge> queuei;
                queuei.push_back(ei);
                voisins.insert( std::pair< node,std::list<edge> > (*nodei,queuei) );

            }
            //ET
            //----------Insere Edge e a la map voisin  pour j
            map<node, std::list<edge> >::iterator itj ;
            iti=voisins.find((*nodej)) ; //ref unique de nodei dans nodes //ex : i
            if(iti!=voisins.end()){ //node i pas incore dans nodes
                iti->second.push_back(ei);
            }
            else{
                std::list<edge> queuej;
                queuej.push_back(ei);
                voisins.insert( std::pair< node,std::list<edge> > (*nodej,queuej) );
            }

        }
    }

}


//Constructeur à partir de Edge donnés :

boostgraph::boostgraph(std::string file) {

    //LECTURE FICHIER
    std::cout<<"Loading road networks from file " << file << " ... "<<std::endl;
    std::string ligne;
    ifstream Myfile;
    Myfile.open(file);
    getline(Myfile,ligne);

    //PREMIERE LIGNE FICHIER (info : nb de noeuds, edges)
    while (ligne[0] != 'p')
        getline(Myfile,ligne);
    std::vector<std::string> sep = split(ligne, ' ' );

    this->V = std::stoi(sep[2]);
    this->nbEdges = std::stoi(sep[3]);
    //std::cout<<" nbedges "<<nbEdges<<std::endl;

    //LECTURE LIGNE
    while (Myfile) {
        getline(Myfile,ligne);
        std::vector<std::string> sep = split(ligne, ' ' );
        if (ligne[0]=='a') {
            int i = std::stoi(sep[1]);
            int j = std::stoi(sep[2]);
            int v = std::stoi(sep[3]);
            node*nodei = newnode(i,"Null");
            node*nodej = newnode(j,"Null");
            edge ei=*newedge(nodei,nodej,v);
            //edge ej=*newedge(nodej,nodei,v);

            //INSERE noeuds de valeurs  i,j
            nodes.insert(*nodei);
            nodes.insert(*nodej);
            edges.push_back(ei); //tous les edges
            // edges.push_back(ej); //tous les edges

            //Insere Edge e a la map voisin  pour i
            map<node, std::list<edge> >::iterator iti ;
            iti=voisins.find((*nodei)) ; //ref unique de nodei dans nodes //ex : i
            if(iti!=voisins.end()){ //node i pas incore dans nodes
                iti->second.push_back(ei);
            }
            else{
                std::list<edge> queuei;
                queuei.push_back(ei);
                voisins.insert( std::pair< node,std::list<edge> > (*nodei,queuei) );

            }
            //Insere Edge e a la map voisin  pour j
            map<node, std::list<edge> >::iterator itj ;
            iti=voisins.find((*nodej)) ; //ref unique de nodei dans nodes //ex : i
            if(iti!=voisins.end()){ //node i pas incore dans nodes
                iti->second.push_back(ei);
            }
            else{
                std::list<edge> queuej;
                queuej.push_back(ei);
                voisins.insert( std::pair< node,std::list<edge> > (*nodej,queuej) );
            }

        }
    }
    Myfile.close();
    std::cout <<("Graph created")<<std::endl;
}




// -------FONCTIONS-------------------

node* boostgraph::newnode(int value,std::string nom){ //cree le noeud
    node *nptr=new node;
    nptr->numero=value;
    nptr->cluster=-1;
    nptr->name=nom;
    //nptr->next=NULL;
    return nptr;
}

edge* boostgraph::newedge(node *i, node* j,double w){
    edge *e = new edge;
    e->start = i;
    e->finish=j;
    e->poids=w;
    return e;
}


std::vector<std::string> boostgraph::split(std::string str, char delimiter) {
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}



// -------PRINT-------------------

void boostgraph::printGraph(){
    std::cout<<"PrintGraph : "<<std::endl;

    for(map<node, std::list<edge> >::const_iterator it = voisins.begin();
        it != voisins.end(); ++it) {
        std::cout << "Noeud : "<<it->first.numero << std::endl ;
        std::cout << "Arretes : " << std::endl ;
        printEdges(it->second);
    }
}


void boostgraph::printEdges(std::set<edge> q){
    std::cout<<"PrintEdges : "<<std::endl;
    std::set<edge>::iterator it;
    for (it = q.begin(); it != q.end(); ++it)
    {
        edge e=*it;
        e.print();
    }
    std::cout << std::endl;
}


void boostgraph::printEdges(std::list<edge> q){
    std::cout<<"PrintEdges : "<<std::endl;
    std::list<edge>::iterator it;
    for (it = q.begin(); it != q.end(); ++it)
    {
        edge e=*it;
        e.print();
    }
    std::cout << std::endl;
}


void boostgraph::printNode(std::set<node> q){
    std::cout<<"PrintNode : "<<std::endl;
    std::set<node>::iterator it;
    for (it = q.begin(); it != q.end(); ++it)
    {
        if(it->name!="Null"){
            std::cout<<"Nom : "<<it->name; }
        std::cout<<" // Numero : "<<it->numero<<std::endl;
    }
    std::cout << std::endl;
}







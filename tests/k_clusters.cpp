#include <iostream>

#include "k_clusters.hpp"
#include "boostgraph.hpp"
#include "kruskal.cpp"
#include "unionfind.cpp"

#include <queue>
#include <set>


kclusters::kclusters( kruskal j,int k){
    _k=k;
    di=j.di;
    vectors=j.vectors;
    marque = new int[j.V];

    //--------- VARIABLES--------------------
    int c=0;             // cluster numero "c"
    std::queue<node> q;  // queue de priority pour rajouter les noeuds connectes

    //  ------- ARBRE REDUIT T--------------
    std::list<edge>  T=j.MST;
    Tprime = j.MST;
    T.sort();
    Tprime.sort();

    for(int i =0;i<k-1;i++){
        isoles.insert(*T.front().start);
        isoles.insert( *T.front().finish);
        reduced.insert( T.front());
        T.pop_front();
        Tprime.pop_front(); }

    //-------EXPLORATION DES ARBRES POUR CREER LES CLUSTERS --------

    while(T.size()!=0) {
        std::map<std::string,int > occurences ;
        c=c+1;

        //Initialisation cluster "c" (son premier noeud est "pere")
        edge e = *T.begin();
        node *pere;
        // if(e.start->cluster==-1){
        if (marque[e.start->numero-1]==0){
            pere =e.start;
        }

        else{ pere =e.finish; }
        marque[pere->numero-1]=c;
        q.push(*pere);
        isoles.erase(*pere);
        clusters.insert( std::pair< int, std::set<node> > (c,  std::set<node>()  ));
        clusters[c].insert(*pere);
        occurences[pere->name]=occurences[pere->name]+1;


        //REMPLISSAGE CLUSTER C
        while (q.size()!=0){
            node n = q.front();
            q.pop();
            std::list<edge>::iterator lien;

            for(lien=T.begin();lien!=T.end();lien++){

                //--------Ajout du noeud END--------------------------
                if(lien->start->numero==n.numero ){
                    node *ajout = lien->finish;

                    if (marque[ajout->numero-1]==0){
                        q.push(*ajout);
                    }
                    marque[ajout->numero-1]=c; //initialise le cluster à c

                    if (isoles.find(*ajout)!=isoles.end()){ //enleve le noeud des isoles
                        isoles.erase(*ajout); }

                    clusters[c].insert(*ajout);
                    occurences[ajout->name]=occurences[ajout->name]+1;
                    T.erase(lien);
                }

                //OU


                // -----Ajout du noeud START-----------------------
                if(lien->finish->numero==n.numero ){
                    node *ajout = lien->start;

                    if (marque[ajout->numero-1]==0){
                        q.push(*ajout);
                    }
                    if (isoles.find(*ajout)!=isoles.end()){
                        isoles.erase(*ajout);
                    }
                    marque[ajout->numero-1]=c;
                    clusters[c].insert(*ajout);
                    occurences[ajout->name]=occurences[ajout->name]+1;
                    T.erase(lien);
                }
            }
        }


        //NOM DU CLUSTER DONNE EN FONCTION DE L'OCCURENCE

        std::map<std::string,int>::iterator it;
        int max = 0;
        std::string nom;
        for(it=occurences.begin();it!=occurences.end();it++){
            if (max<it->second){
                max=it->second;
                nom=it->first;
            }
        }

        //NOM DU CLUSTER DONNE EN FONCTION DU POURCENTAGE

       // std::cout<<"pourcentage"<<std::endl;
       /* std::map<std::string,int>::iterator it;
        int max = 0;
        double pourcentage=0.0;
        std::string nom;
        for(it=occurences.begin();it!=occurences.end();it++){
        //pourcentage dappartion dun nom "it->second" par rapport à son occurence total dans la base de données
            pourcentage = 100* (it->second)/(j.occurences[it->first]);
            if (max<pourcentage){
                max=pourcentage;
                nom=it->first;
            }
        }*/

        correspondance.insert(std::pair<int,std::string> (c,nom));

    }

    nb_clusters_reel=c;



    //AJOUT DES NOEUDS ISOLES (clusters de taille 1)
    for (node e : isoles){
        c=c+1;
        std::set<node> m;
        marque[e.numero-1]=c;
        m.insert(e);
        clusters.insert( std::pair< int, std::set<node> > (c,  m ));
        correspondance.insert(std::pair<int,std::string> (c,"Bruit"));
    }

}


kclusters::~kclusters(){
    delete marque;
    delete barycentres;

}



//------------FONCTIONS--------------------


void kclusters::print(){
    std::cout<<std::endl;
    std::cout<<"DEBUT CLUSTERING"<<std::endl;
    // std::cout<<"Nb Clusters k :"<<this->_k<<std::endl;
    // std::cout << std::endl;
    std::map< int, std::set<node> >::iterator it;
    for ((it) = clusters.begin(); it != clusters.end(); ++it)
    {
        std::cout<<"Num cluster :"<<it->first<<std::endl;
        std::cout<<"Nom cluster :"<<correspondance[it->first]<<std::endl;
        std::cout<<"Noeuds : "<<std::endl;
        // for (int i =0;i<V;i++)
        printNode((it->second));
        std::cout<<std::endl;
    }
    std::cout<<"FIN CLUSTERING K  "<<std::endl;
    std::cout<<"Nb Clusters k :"<<this->_k<<std::endl;
    std::cout<<"Nb_reel de Clusters (sans bruit) "<<nb_clusters_reel<<std::endl;
    //std::cout<<"Erreur : "<<this->error()<<"%"<<std::endl;
    std::cout<<"Inter/(Inter+Intra)*100 : "<<100*interclusters()/(interclusters()+intraclusters())<<std::endl;
    std::cout<<std::endl;


}



double kclusters::error(){ //Nombre total d'erreur de clustering sur nombre total de noeuds
    double error=0.0;
    double tot=0.0;
    std::map<int,std::set<node> >::iterator it;
    for(it=clusters.begin();it!=clusters.end();it++   ){
        tot=tot+it->second.size();
        int clu = it->first;
        std::string nom = correspondance[clu];
        std::set<node> clusterI = it->second;
        std::set<node>::iterator noeud;
        for(noeud=clusterI.begin();noeud!=clusterI.end();noeud++){
            if((nom)!=noeud->name){
                error=error+1;
            }
        }
    }
    return error/tot;
}

double kclusters::true_error(){ //Nombre total d'erreur de clustering sur nombre total de noeuds
    double error=0.0;
    double tot=0.0;
    for(int i=1;i<=nb_clusters_reel;i++){ //cluster i
        std::string nom = correspondance[i];
        std::set<node> clusterI = clusters[i];
        std::set<node>::iterator noeud;
        for(noeud=clusterI.begin();noeud!=clusterI.end();noeud++){
            tot=tot+1;
            if((nom)!=noeud->name){
                error=error+1;
            }
        }
    }
    return error/tot;
}



double kclusters::interclusters(){ //Distance moyenne des barycentres de chaque clusters au barycentre
    double sum=0.0 ;
    int tot=0;
    for(int i=0;i<nb_clusters_reel;i++){//bary clusters
        sum=sum+di->calcul(barycentres[i],barycentre);
        tot=tot+1;
    }
    return sum/tot;

}



double kclusters::intraclusters(){ //Distance moyenne des points au barycentre de leur cluster
    double sum=0.0 ;
    int tot=0;
    for(int i=0;i<nb_clusters_reel;i++){//bary clusters
        std::set<node> clusterI = clusters[i+1];
        std::set<node>::iterator noeud;
        for(noeud=clusterI.begin();noeud!=clusterI.end();noeud++){
            sum=sum+di->calcul(barycentres[i],vectors[noeud->numero-1]);
            tot=tot+1;
        }
    }
    return sum/tot;
}


double kclusters::interclusters_simple(){ //Moyenne des poids interclusters
    double sum=0.0 ;
    int tot=0;
    std::set<edge>::iterator it;
    for(it=reduced.begin();it!=reduced.end();it++){//bary clusters
        sum=sum+it->poids;
        tot=tot+1;
    }
    return sum/tot;

}

double kclusters::intraclusters_simple(){ //Moyenne des poids intraclusters
    double sum=0.0 ;
    int tot=0;
    std::list<edge>::iterator it;
    for(it=Tprime.begin();it!=Tprime.end();it++){//bary clusters
        sum=sum+it->poids;
        tot=tot+1;
    }
    return sum/tot;
}


void kclusters::printNode(std::set<node> q){
    std::set<node>::iterator it;
    for (it = q.begin(); it != q.end(); ++it)
    {
        if(it->name!="Null"){
            std::cout<<"  -Nom (réel) : "<<it->name; }
        std::cout<<" // Numero : "<<it->numero<<"// Clusters (produit): "<<marque[it->numero-1]<<std::endl;
    }
    std::cout << std::endl;
}


void kclusters::setBarycentres(){
    barycentres = new item[nb_clusters_reel];

    std::map<int,std::set<node> >::iterator it;
    int dim=vectors[1].dim;
    barycentre = item(1000,dim);
    barycentre.name="Barycentre";


    for(int i=0;i<nb_clusters_reel;i++){
        barycentres[i]= item(i,dim);
        barycentres[i].name=correspondance[i+1];

    }
    for(int d=0;d<dim;d++){
        for(int i=0;i<nb_clusters_reel;i++){//bary clusters
            std::set<node>::iterator noeud;
            for(noeud = clusters[i+1].begin();noeud!=clusters[i+1].end();noeud++){
                barycentres[i].coord[d]=barycentres[i].coord[d]+vectors[noeud->numero-1].coord[d]; //Barycentres I
            }
            barycentres[i].coord[d]= barycentres[i].coord[d]/clusters[i+1].size(); //Barycentres I
            barycentre.coord[d]= (barycentre.coord[d]+ barycentres[i].coord[d]); //Barycentre total
        }
        barycentre.coord[d]=barycentre.coord[d]/nb_clusters_reel; //Barycentre total


    }

}

void kclusters::printBary(){
    std::cout<<std::endl;
    std::cout<<"Barycentres : "<<std::endl;
    std::cout<<std::endl;
    for(int i=0;i<nb_clusters_reel;i++){
        barycentres[i].print();
    }
    barycentre.print();
}















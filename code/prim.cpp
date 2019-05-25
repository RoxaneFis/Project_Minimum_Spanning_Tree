#include "prim.hpp"
//#include "boostgraph.hpp"
#include <set>
#include <map>


//------------CONSTRUCTEURS--------------------

Prim::Prim(node& start, boostgraph&_g)
{
    // A. INITIALISATION

    count=0;
    std::priority_queue<edge> q;

    //remplit nonvisite
    std::set <node> nonvisite;
    std::set<node>::iterator itp ;
    for( itp=_g.nodes.begin(); itp!=_g.nodes.end();itp++){
        nonvisite.insert(*itp);
    }

    //Voisin : liste de voisin de start
    std::map<node, std::list<edge> >::iterator it ;
    it=_g.voisins.find((start)) ; //ref unique de nodei dans nodes //ex : i
    std::list<edge> voisin =it->second;
    addAllqueueEdge(q,voisin);
    nonvisite.erase(start);


    // B. BOUCLE
    while(!q.empty()){
        edge p = q.top();
        q.pop();


        if(nonvisite.find(*p.finish)!=nonvisite.end() ){ //nouveau node pas deja visite
            nonvisite.erase(*p.finish);

            (MST).push_back(p); //rajoute edge connecte new noeud
            count=count+p.poids;

            if(_g.voisins.find(*p.finish)!=_g.voisins.end()){ //noeud noeud a des voisins
                addAllqueueEdge(q, _g.voisins.find(*p.finish)->second,p);
            }//rajout des voisins
        }


        if(nonvisite.find(*p.start)!=nonvisite.end() ){ //nouveau node pas deja visite
            nonvisite.erase(*p.start);

            (MST).push_back(p); //rajoute edge connecte new noeud
            count=count+p.poids;
            if(_g.voisins.find(*p.start)!=_g.voisins.end()){ //noeud noeud a des voisins
                addAllqueueEdge(q, _g.voisins.find(*p.start)->second,p);
            }//rajout des voisins
        }

    }
    std::cout<<"end"<<std::endl;
}


//------------FONCTIONS--------------------

void Prim::addAllqueueEdge(std::priority_queue<edge> &q,   std::list<edge> liste ){
    std::list<edge>::iterator it2;
    edge e;
    for (it2 = liste.begin(); it2 != liste.end(); ++it2) {
        e=*it2;
        q.push(e);
    }

}
void Prim::addAllqueueEdge(std::priority_queue<edge> &q,   std::list<edge> liste,edge& p ){
    std::list<edge>::iterator it2;
    edge e;
    for (it2 = liste.begin(); it2 != liste.end(); ++it2) {
        e=*it2;
        if(!(e.start==p.start &&      e.finish==p.finish)){
            q.push(e);}
    }

}





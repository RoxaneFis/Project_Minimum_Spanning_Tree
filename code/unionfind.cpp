
#include <map>

#include "unionfind.hpp"
#include "boostgraph.hpp"


//------------CONSTRUCTEURS--------------------

unionfind::unionfind(){
    parent =  std::map < node,node >();

}


//------------FONCTIONS--------------------

void unionfind::SetUp(boostgraph& _b){
    //remplit la collection
    std::set< node >::iterator itp ;
    for( itp = _b.nodes.begin(); itp != _b.nodes.end(); ++itp) {
        parent.insert( std::pair< node,node > (*itp,*itp));
    }
}

node unionfind::trouver(node& x){
    node pere=parent[x];
    if(pere.numero==x.numero){
        return x;
    }
    else {
        parent[x]=pere;
        return trouver(pere); }
}

void unionfind::uni(node& x, node& y){
    node irep = trouver(x);
    node jrep = trouver(y);
    if(irep.numero==jrep.numero) {
        return;
    }
    else {
        parent[jrep]=parent[irep];
        return;
    }
}

void unionfind::print(node& enfant){
    std::cout<<"enfant : " <<enfant.numero;
    std::cout<<"Pere : " <<parent[enfant].numero<<std::endl;

}

void unionfind::print(){
    std::map < node,node >::iterator it;
    for (it=parent.begin(); it!=parent.end();it++) {
        std::cout<<"enfant : " <<it->first.numero;
        std::cout<<" Pere : " <<parent[it->first].numero<<std::endl;
    }
}






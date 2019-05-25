#ifndef ITEM_H
#define ITEM_H

#include "boostgraph.hpp"
#include <unordered_set>
#include <queue>
#include <map>


class item
{
public:

    int numero;
    double * coord;
    int dim;
    std::string name;

    //constructeurs
    item(int _numero,int _dim);
    item();

    //Fonction
    //double dist(item &autre);
    void print();

};






#endif // ITEM_H





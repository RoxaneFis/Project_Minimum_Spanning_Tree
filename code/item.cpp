#include <iostream>
#include <cmath>
#include <cassert>
#include "item.hpp"


item::item(){}
item::item(int _numero,int _dim){

    numero=_numero;
    dim=_dim;
    coord=new double[dim] ;
    for(int m = 0; m < dim; m++){
        coord[m] = 0.0;}
}

void item::print(){
    std::cout<<"Name : "<<name<<std::endl;
    std::cout<<"Numero : "<<numero<<std::endl;
    std::cout << coord[0];
    for (int j = 1; j < dim; j++)
        std::cout << ' ' << coord[j];
    std::cout << std::endl;
    std::cout << std::endl;

}





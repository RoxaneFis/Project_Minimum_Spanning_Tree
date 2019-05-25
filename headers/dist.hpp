#ifndef DISTANCE_H
#define DISTANCE_H

#include "item.cpp"


class dist
{
public:
    // virtual double calcul(item& a,item& b) ;
};

class Eucli : public dist{
public:

    double calcul(item& a,item& b) {

        double sqd = 0.0;
        for (int m = 0; m < a.dim; m++){
            sqd += (a.coord[m]-b.coord[m]) * (a.coord[m]-b.coord[m]);}
        return sqrt(sqd);

    }


};

#endif // DISTANCE_H


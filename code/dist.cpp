//#include "dist.hpp"
#include "item.cpp"

class dist{
public:
    dist(){double calcul(item& a,item& b); }
    virtual double calcul(item& a,item& b)=0;
};

class Eucli : public dist{
public:
    double calcul(item& a,item& b) {
        double sqd = 0.0;
        for (int m = 0; m < a.dim; m++){
            sqd += (a.coord[m]-b.coord[m]) * (a.coord[m]-b.coord[m]);}
        return sqrt(sqd); }
};

class Manhattan : public dist{
public:
    double calcul(item& a,item& b) {
        double sqd = 0.0;
        for (int m = 0; m < a.dim; m++){
            sqd += std::abs(a.coord[m]-b.coord[m]) ;}
        return (sqd);

    }
};

class Inf : public dist{
public:
    double calcul(item& a,item& b) {
        double max = 0.0;
        for (int m = 0; m < a.dim; m++){
            if(std::abs(a.coord[m]-b.coord[m]) >max){
                max=std::abs(a.coord[m]-b.coord[m]);
            }

        }
    return (max);
    }
};


/*class Manhattan : public dist{
public:
    double calcul(item& a,item& b) {
        double sqd = 0.0;
        for (int m = 0; m < a.dim; m++){
            sqd += std::abs(a.coord[m]-b.coord[m]) ;}
        return sqrt(sqd);

    }
};*/

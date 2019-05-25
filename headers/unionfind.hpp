#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "boostgraph.hpp"

class unionfind
{
public:
    std::map < node,node >  parent;
    unionfind();

    void SetUp(boostgraph& _b);
    //void SetUp(graphpartiel& _b);
    node trouver(node& x);
    void uni(node& x, node& y);
    void print(node& parent);
    void print();






};
#endif // UNIONFIND_H

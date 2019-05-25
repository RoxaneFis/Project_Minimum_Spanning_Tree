#ifndef BORUVKA_HPP
#define BORUVKA_HPP
#include "boostgraph.hpp"
#include "unionfind.hpp"


class boruvka
{
public:
    int count;
    std::map<node, int> cheapest;
    std::list<edge>  MST;
    boruvka(boostgraph& _g);
};

#endif // BORUVKA_HPP

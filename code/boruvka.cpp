#include "boruvka.hpp"

boruvka::boruvka(boostgraph& _g)
{
    int V = _g.V;
    std::set<node> N = _g.nodes;
    int E = _g.nbEdges;
    std::list<edge> edge = _g.edges;

    //Creating array storing, for each vertex, the cheapest edge coming out of it
    int *cheapest = new int[V];
    for (int v = 0; v < V; ++v) {
        cheapest[v] = -1;
    }

    count=0;

    //Creating unionFind structure
    unionfind *u = new unionfind();
    u->SetUp(_g);

    //Filling array of edges Etab
    struct edge* Etab = new struct edge [E];
    std::list<struct edge>::iterator it;
    int i = 0;
    for (it = (edge).begin(); it != (edge).end(); ++it) {
        Etab[i] = *it;
        i++;
    }



    // Initially there are V different trees.
    // Finally there will be one tree that will be MST
    int numberTrees = V;
    // Keep combining components (or sets) until all
    // compnentes are not combined into single MST.
    while (numberTrees > 1)
    {
        // Everytime initialize cheapest array
        for (int v = 0; v < V; ++v)
        {
            cheapest[v] = -1;
        }

        // Traverse through all edges and update
        // cheapest of every component
        for (int i=0; i<E; i++)
        {
            // Find set of two vertices of current edge
            int set1 = u->trouver(*(Etab[i].start)).numero;
            int set2 = u->trouver(*(Etab[i].finish)).numero;

            // If two vertices of current edge belong to
            // same set, ignore current edge
            if (set1 == set2)
                continue;

            // Else check if current edge is closer to previous
            // cheapest edges of set1 and set2
            else
            {
                if (cheapest[set1] == -1 ||
                        Etab[cheapest[set1]].poids > Etab[i].poids)
                    cheapest[set1] = i;

                if (cheapest[set2] == -1 ||
                        Etab[cheapest[set2]].poids > Etab[i].poids)
                    cheapest[set2] = i;
            }
        }

        // Consider the above picked cheapest edges and add them
        // to MST
        for (int i=0; i<V; i++)
        {
            if (cheapest[i] != -1)
            {
                node set1 = u->trouver(*(Etab[cheapest[i]].start));
                node set2 = u->trouver(*(Etab[cheapest[i]].finish));

                int s1 = set1.numero;
                int s2 = set2.numero;

                if (s1 == s2)
                    continue;
                count += Etab[cheapest[i]].poids;
                MST.push_back(Etab[cheapest[i]]);

                // Do a union of set1 and set2 and decrease number of trees
                u->uni(set1, set2);
                numberTrees--;
            }
        }

    }
    return;
}

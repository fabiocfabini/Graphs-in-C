#include <stdio.h>
#include "../includes/Graph.h"

int dfsRec(Graph g, int origin, int distance[], int tree[]){
    int count = 1;
    
    for(Adj aux = g[origin]; aux; aux = aux->dest){
        if(distance[aux->vertice] == -1){
            distance[aux->vertice] = distance[origin] + aux->weight;
            tree[aux->vertice] = origin;
            count += dfsRec(g, aux->vertice, distance, tree);
        }
    }

    return count;
}

int depth_first_search(Graph g, int NV, int origin, int distance[], int tree[]){
    // Cleaning the input arrays
    for(int i = 0; i < NV; distance[i] = -1, tree[i] = -2, i++);

    // Setting the defualt values for origin
    tree[origin] = -1; distance[origin] = 0;

    return dfsRec(g, origin, distance, tree);
}



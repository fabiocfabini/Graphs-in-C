#include <stdio.h>
#include <string.h>

#include "../includes/Graph.h"

int dfsRec(Graph g, int origin, int distance[], int tree[]){
    int count = 1;

    for(Adj aux = g->nodes[origin]; aux; aux = aux->dest){
        if(distance[aux->vertice] == -1){
            distance[aux->vertice] = distance[origin] + aux->weight;
            tree[aux->vertice] = origin;
            count += dfsRec(g, aux->vertice, distance, tree);
        }
    }

    return count;
}

int depth_first_search(Graph g, int origin, int distance[], int tree[]){
    // Cleaning the input arrays
    for(int i = 0; i < g->NV; distance[i] = -1, tree[i] = -2, i++);

    // Setting the defualt values for origin
    tree[origin] = -1; distance[origin] = 0;

    return dfsRec(g, origin, distance, tree);
}

int breadth_first_search(Graph g, int origin, int distance[], int tree[]){
    int fringe[g->NV]; int current_node = origin, start = 0, end = 0, count = 0;
    Adj aux;

    // Initializing the arays
    for(int i = 0; i < g->NV; tree[i] = -2, distance[i] = -1, i++);

    // Setting up the default values of origin
    fringe[end++] = origin; tree[origin] = -1; distance[origin] = 0;

    while(end > start){
        // Remove node from 
        current_node = fringe[start++]; count++;

        // look at all the the adjacents of current_node
        for(aux = g->nodes[current_node]; aux; aux = aux->dest){
            // if the distance to that node is still -1 (assuming only positive distances)
            if(distance[aux->vertice] == -1){
                // add the node to the fringe
                fringe[end++] = aux->vertice;

                // update its parent in tree
                tree[aux->vertice] = current_node;

                // update its distance (assuming only weights of 1) 
                distance[aux->vertice] = 1 + distance[current_node];
            }
        }
    }

    return count;
}


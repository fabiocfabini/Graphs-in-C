#include <stdio.h>
#include <stdlib.h>
#include "../includes/Graph.h"

//* free functions
void free_graph(Graph g, int NV){
    for(int i = 0; i < NV; i++){
        free_adj(g[i]);
    }
    free(g);
}

void free_adj(Adj a){
    while(a){
        Adj tmp = a->dest;
        free(a);
        a = tmp;
    }
}


//* stdout functions
void display_graph(Graph g, int NV){
    for(int i = 0; i < NV; i++){
        printf("%d: ", i);
        for(Adj aux = g[i]; aux; aux = aux->dest){
            printf("%d(%d) -> ", aux->vertice, aux->weight);
        }printf("NULL\n");
    }
}

void display_mgraph(MGraph g, int NV){
    for (int row = 0; row < NV; row++){
        for (int col = 0; col < NV; col++){
            printf("%d ", g[I(row, col, NV)]);
        }
        printf("\n");
    }
}

void display_adj(Adj a){
    while(a){
        printf("(%d, %d) -> ", a->vertice, a->weight);
        a = a->dest;
    }printf("NULL\n");
}


//* Construction Functions
void append_node(int vertice, int weight, Adj* dest){   
    while(*dest) dest = &(*dest)->dest;

    Adj new = push_node(vertice, weight, *dest);
    *dest = new;
}

Adj push_node(int vertice, int weight, Adj dest){
    Adj new = malloc(sizeof(Node));

    if(new){
        new->vertice = vertice;
        new->weight = weight;
        new->dest = dest;
    }

    return new;
}


//* Destruction Functions
void init_adj(Adj* a, int* vertice, int* weight){
    while((*a) && (*a)->dest){
        a = &(*a)->dest;
    }
    *vertice = (*a)->vertice;
    *weight = (*a)->weight;
    free(*a); *a = NULL;
}

int remove_node_by_vertice(Adj* a, int vertice){
    int r = 1;
    while(*a && (*a)->vertice != vertice) a = &(*a)->dest;

    if(*a){
        Adj tmp = (*a)->dest;
        free(*a);
        *a = tmp;
        r = 0;
    }

    return r;
}

int remove_node_by_weight(Adj* a, int weight){
    int r = 1;
    while(*a && (*a)->weight != weight) a = &(*a)->dest;

    if(*a){
        Adj tmp = (*a)->dest;
        free(*a);
        *a = tmp;
        r = 0;
    }

    return r;
}

int remove_node_by_dest(Adj* a, Adj dest){
    int r = 1;
    while(*a && (*a)->dest != dest) a = &(*a)->dest;

    if(*a){
        Adj tmp = (*a)->dest;
        free(*a);
        *a = tmp;
        r = 0;
    }

    return r;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../includes/Graph.h"

// void set_node_color(Graph g, int vertice, char *color)
// {
//     for (int i = 0; i < g->NV; i++)
//     {
//         for (Adj aux = g->nodes[i]; aux; aux = aux->dest)
//         {
//             if (aux->vertice == vertice)
//             {
//                 strncpy(aux->color, color, COLOR_SIZE);
//             }
//         }
//     }
// }

//* free functions
void free_graph(Graph g)
{
    for (int i = g->NV - 1; i >= 0; i--)
    {
        free_adj(g->nodes[i]);
    }
    free(g->nodes);
    free(g->colors);
    free(g);
}

void free_adj(Adj a)
{
    while (a)
    {
        Adj tmp = a->dest;
        free(a);
        a = tmp;
    }
}

//* stdout functions
void display_graph(Graph g)
{
    printf("Node Colors: [");
    for (int i = 0; i < g->NV; i++)
    {
        printf("%d:%d, ", i, g->colors[i]);
    }
    printf("];\n\n");

    for (int i = 0; i < g->NV; i++)
    {
        printf("%d: ", i);
        for (Adj aux = g->nodes[i]; aux; aux = aux->dest)
        {
            printf("(%d, %d) -> ",aux->vertice, aux->weight);
        }
        printf("NULL\n");
    }printf("\n");
}

void display_mgraph(MGraph g, int NV)
{
    for (int row = 0; row < NV; row++)
    {
        for (int col = 0; col < NV; col++)
        {
            printf("%d ", g[I(row, col, NV)]);
        }
        printf("\n\n");
    }
}

void display_adj(Adj a)
{
    while (a)
    {
        printf("(%d, %d) -> ", a->vertice, a->weight);
        a = a->dest;
    }
    printf("NULL\n");
}

//* Construction Functions
void append_node(int vertice, int weight, Adj *dest)
{
    while (*dest)
        dest = &(*dest)->dest;

    Adj new = push_node(vertice, weight, *dest);
    *dest = new;
}

Adj push_node(int vertice, int weight, Adj dest)
{
    Adj new = malloc(sizeof(Node));

    if (new)
    {
        new->vertice = vertice;
        new->weight = weight;
        new->dest = dest;
    }

    return new;
}

//* Destruction Functions
void init_adj(Adj *a, int *vertice, int *weight)
{
    while ((*a) && (*a)->dest)
    {
        a = &(*a)->dest;
    }
    *vertice = (*a)->vertice;
    *weight = (*a)->weight;
    free(*a);
    *a = NULL;
}

int remove_node_by_vertice(Adj *a, int vertice)
{
    int r = 1;
    while (*a && (*a)->vertice != vertice)
        a = &(*a)->dest;

    if (*a)
    {
        Adj tmp = (*a)->dest;
        free(*a);
        *a = tmp;
        r = 0;
    }

    return r;
}

int remove_node_by_weight(Adj *a, int weight)
{
    int r = 1;
    while (*a && (*a)->weight != weight)
        a = &(*a)->dest;

    if (*a)
    {
        Adj tmp = (*a)->dest;
        free(*a);
        *a = tmp;
        r = 0;
    }

    return r;
}

int remove_node_by_dest(Adj *a, Adj dest)
{
    int r = 1;
    while (*a && (*a)->dest != dest)
        a = &(*a)->dest;

    if (*a)
    {
        Adj tmp = (*a)->dest;
        free(*a);
        *a = tmp;
        r = 0;
    }

    return r;
}

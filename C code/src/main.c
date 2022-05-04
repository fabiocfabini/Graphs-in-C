#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include "../includes/Graph.h"
#include "../includes/Paths.h"

char* graph_name = "default.txt";

int main(int argc, char const *argv[]) {
    Graph g = build_graph(graph_name);
    if(g){
        display_graph(g);

        int NV = g->NV;
        int dist[NV], tree[NV];
        int count = breadth_first_search(g, 0, dist, tree);

        printf("distance: ");
        for(int i = 0; i < count; i++){
            if(dist[i] != -1) printf("(i:%d, %d) ", i, dist[i]);
        }printf("\n");

        printf("tree: ");
        for(int i = 0; i < count; i++){
            if(tree[i] != -2) printf("(i:%d, %d) ", i, tree[i]);
        }printf("\n");

        printf("Vertices found. %d\n", count);

        free_graph(g);
    }

    return 0;
}

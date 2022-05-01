#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include "../includes/Graph.h"
#include "../includes/Paths.h"

char* graph_name = "first.txt";

int main(int argc, char const *argv[]) {
    int NV;
    Graph g = build_graph(graph_name, &NV);
    if(g) display_graph(g, NV);

    int dist[NV], tree[NV];
    int count = depth_first_search(g, NV, 0, dist, tree);

    for(int i = 0; i < NV; i++){
        printf("(i:%d, %d) ", i, dist[i]);
    }printf("\n");

    for(int i = 0; i < NV; i++){
        printf("(i:%d, %d) ", i, tree[i]);
    }printf("\n");

    printf("Vertices found. %d\n", count);

    free_graph(g, NV);

    return 0;
}

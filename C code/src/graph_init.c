#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linux/limits.h>
#include "../includes/Graph.h"
#include "../includes/Paths.h"

MGraph build_mgraph(const char* graph_name, int* NV){
    char graph_file_path[PATH_MAX + 1];
    if(!get_graph_file_path(graph_file_path, graph_name)){
        printf("Graph %s does not exists in path:\n\t" DATA_DIRECTORY "\n\n", graph_name);
        return NULL;
    }

    FILE *f = fopen(graph_file_path, "r");

    if(f == NULL){
        printf("Error opening file!\n");
        return NULL;
    }

    fscanf(f, "%d ", NV);

    MGraph g = malloc((*NV) * (*NV) * sizeof(int));
    for(int row = 0; row < *NV; row++){
        for(int col = 0; col < *NV; col++){
            fscanf(f, "%d ", g + I(row, col, *NV));
        }
    }

    fclose(f);
    return g;
}

Graph build_graph(const char* graph_name){
    char graph_file_path[PATH_MAX + 1];
    if(!get_graph_file_path(graph_file_path, graph_name)){
        printf("Graph %s does not exists in path:\n\t" DATA_DIRECTORY "\n\n", graph_name);
        return NULL;
    }

    FILE *f = fopen(graph_file_path, "r");

    if(f == NULL){
        printf("Error opening file!\n");
        return NULL;
    }

    int NV;
    fscanf(f, "%d ", &NV);

    int weight;
    Graph g = malloc(sizeof(graph));
    g->NV = NV;
    g->nodes = malloc(NV * sizeof(Adj));
    g->colors = calloc(NV, sizeof(Color));
    for(int row = 0; row < NV; row++){
        g->nodes[row] = NULL;
        for(int col = 0; col < NV; col++){
            fscanf(f, "%d ", &weight);
            if(weight){
                g->nodes[row] = push_node(col, weight, g->nodes[row]);
            }
        }
    }

    fclose(f);
    return g;
}
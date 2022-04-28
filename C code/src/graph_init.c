#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linux/limits.h>
#include "../headers/Graph.h"
#include "../headers/Paths.h"

MGraph build_mgraph(const char* graph_name, int* NV){
    char graph_file_path[PATH_MAX + 1];
    if(!get_graph_file_path(graph_file_path, graph_name)){
        printf("Check if the graph %s exists in \n\t[" DATA_DIRECTORY "]\n\n", graph_name);
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

Graph build_graph(const char* graph_name, int* NV){
    char graph_file_path[PATH_MAX + 1];
    if(!get_graph_file_path(graph_file_path, graph_name)){
        printf("Check if the graph %s exists in \n\t[" DATA_DIRECTORY "]\n\n", graph_name);
        return NULL;
    }

    FILE *f = fopen(graph_file_path, "r");

    if(f == NULL){
        printf("Error opening file!\n");
        return NULL;
    }

    fscanf(f, "%d ", NV);

    int weight;
    Adj aux;
    Graph g = malloc(sizeof(Adj) * (*NV));
    for(int row = 0; row < *NV; row++){
        g[row] = NULL; aux = NULL;
        for(int col = 0; col < *NV; col++){
            fscanf(f, "%d ", &weight);
            if(weight){
                Adj new = push_node(col, weight, aux);
                aux = new;
            }
        }
        g[row] = aux;
    }

    fclose(f);
    return g;
}
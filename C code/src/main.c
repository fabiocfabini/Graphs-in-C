#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include "../headers/Graph.h"
#include "../headers/Paths.h"

char* graph_name = "second.txt";

int main(int argc, char const *argv[]) {
    int NV;
    MGraph m = build_mgraph(graph_name, &NV);
    if(m) display_mgraph(m, NV);

    Graph g = build_graph(graph_name, &NV);
    if(g) display_graph(g, NV);

    free(m);
    free_graph(g, NV);

    return 0;
}
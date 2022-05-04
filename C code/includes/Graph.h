#ifndef __HGRAPH__
#define __HGRAPH__

//! Macros
#define I(row, col, NV) (row*NV + col)

//! Structs
typedef enum _Color{
    RED,
    YELLOW,
    GREEN
} Color;


typedef int* MGraph;

typedef struct _Node{
    int weight;
    int vertice;
    struct _Node* dest;
}Node, *Adj;

typedef struct _graph{
    int NV;
    Color* colors;
    Adj* nodes;
}graph, *Graph;


//! debug functions

void set_node_color(Graph g, int vertice, char* color);


//! Genreral Functions
//* init from txt file
/**
 * @brief Builds a Matrix graph from a text file
 * 
 * @param graph_name Name of the graph file
 * @param NV Number of vertices
 * @return Graph The graph
 */
MGraph build_mgraph(const char* graph_name, int* NV);

/**
 * @brief Builds a List graph from a text file
 * 
 * @param graph_name Name of the graph file
 * @return Graph The graph
 */
Graph build_graph(const char* graph_name);

//* free functions
/**
 * @brief Frees the memory allocated for a graph
 * 
 * @param g The graph
 * @param NV Number of vertices
 */
void free_graph(Graph g);

/**
 * @brief Frees the memory allocated for a adjancency list
 * 
 * @param g The graph
 * @param NV Number of vertices
 */
void free_adj(Adj a);

//* stdout functions
/**
 * @brief Prints a graph
 * 
 * @param g The graph
 */
void display_graph(Graph g);

/**
 * @brief Prints a matrix graph
 * 
 * @param g The graph
 * @param NV Number of vertices
 */
void display_mgraph(MGraph g, int NV);

/**
 * @brief Prints an adjacency list
 * 
 * @param a The adjacency list
 */
void display_adj(Adj a);

//* Construction Functions
/**
 * @brief Appends a node to an adjacency list
 * 
 * @param vertice The vertice
 * @param weight The weight
 * @param dest The adjacency list
 */
void append_node(int vertice, int weight, Adj* dest);

/**
 * @brief Pushes a node to an adjacency list
 * 
 * @param vertice Te verhtice
 * @param weight The weight
 * @param dest The adjacency list
 * @return Adj The new node
 */
Adj push_node(int vertice, int weight, Adj dest);

//* Destruction Functions
/**
 * @brief Removes the last node from the adjacency list
 * 
 * @param a The adjacency list
 * @param vertice The vertice
 * @param weight The weight
 */
void init_adj(Adj* a, int* vertice, int* weight);

/**
 * @brief Removes node by vertice
 * 
 * @param vertice The vertice
 */
int remove_node_by_vertice(Adj* a, int vertice);

/**
 * @brief Removes node by weight
 * 
 * @param weight The weight
 */
int remove_node_by_weight(Adj* a, int weight);

/**
 * @brief Removes node by dest
 * 
 * @param dest The dest
 */
int remove_node_by_dest(Adj* a, Adj dest);

//! Algorithms

//* Search algorithms
/**
 * @brief Depth-first search
 * 
 * @param g The graph

 * @param origin The start vertice
 * @param distance Array with the distance of all other nodes to origin
 * @param tree Array with the tree of the search
 * 
 * @return int: The number of vertices visited
 */
int depth_first_search(Graph g, int origin, int distance[], int tree[]);
int dfsRec(Graph g, int origin, int distance[], int tree[]);

/**
 * @brief Breadth-first search
 * 
 * @param g The graph

 * @param origin The start vertice
 * @param distance Array with the distance of all other nodes to origin
 * @param tree Array with the tree of the search
 * 
 * @return int: The number of vertices visited
 */
int breadth_first_search(Graph g, int origin, int distance[], int tree[]);

#endif
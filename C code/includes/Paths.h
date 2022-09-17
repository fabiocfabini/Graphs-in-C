#ifndef __PATHS__
#define __PATHS__

#define DEFAULT_TABLE_SIZE 10
#define MAX_GRAPH_NAME_SIZE 50
#define DATA_DIRECTORY "/home/fabiocfabini/Desktop/CS/Graphs-in-C/Data" //! change as needed

#ifdef _WIN32
    #define PATH_SEPARATOR "\\"
#else   
    #define PATH_SEPARATOR '/'
#endif

/**
 * @brief Copies filename with no extension to filename_no_extension. Assumes that enough space has been alocated to filename_no_extension
 * 
 * @param filename_no_extension 
 * @param filename 
 */
void remove_extension(char* filename_no_extension, const char* filename);
void join_paths(char* dest, const char* __restrict__ path1, const char* __restrict__ path2);
char* f_join_paths(const char* __restrict__ path1, const char* __restrict__ path2);
bool get_graph_file_path(char* path, const char* graph_name);

#endif
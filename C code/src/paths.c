#include <stdio.h>
#include <stdarg.h> 
#include <stdlib.h>
#include <stdbool.h>

#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "../includes/Paths.h"

void remove_extension(char* filename_no_extension, const char* filename){
    const char* aux = filename;
    int char_count = 0;

    while(*aux && *aux != '.'){
        char_count++;
        aux++;
    }

    if(! *aux){
        printf("ERROR: Could not remove extension. No '.' char found\n");
        return;
    }

    strncpy(filename_no_extension, filename, char_count); 
    filename_no_extension[char_count] = '\0';
}

void join_paths(char* dest, const char* __restrict__ path1, const char* __restrict__ path2){
    if(*path1 && *path2){
        int size1 = strlen(path1); int size2 = strlen(path2);

        
        // copy path1 to dest
        strncpy(dest, path1, size1);

        // add PATH_SEPARATOR to end of dest
        for(int i = 0; i < size1; i++) dest++;
        *dest = PATH_SEPARATOR;

        // copy path2 to dest
        strncpy(dest+1, path2, size2);
        dest[1+size2] = '\0';
    }
}

char* f_join_paths(const char* __restrict__ path1, const char* __restrict__ path2){
    return NULL;
}

bool get_graph_file_path(char* path, const char* graph_name){
    struct dirent* entry;
    char graph_dir_path[PATH_MAX + 1];
    char graph_name_no_extension[MAX_GRAPH_NAME_SIZE];
    int graph_name_size = strlen(graph_name);
    bool found_path = false;

    remove_extension(graph_name_no_extension, graph_name);
    join_paths(graph_dir_path, DATA_DIRECTORY, graph_name_no_extension);

    DIR* dir = opendir(graph_dir_path);

    if(dir == NULL){
        printf("ERROR: %s\n", strerror(errno));
        return found_path;
    }

    while((entry = readdir(dir)) != NULL){
        // Check if mode of filestat is regular file
        if(strcmp(entry->d_name, graph_name) == 0){
            found_path = true;
            join_paths(path, graph_dir_path, graph_name);
        }
    }

    closedir(dir);

    if(!found_path) *path = '\0';

    return found_path;
}

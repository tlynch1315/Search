/* search.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>

/**
 * Recursively search through the provided root directory
 * @param   root        Path to directory
 * @param   settings    Settings structure
 * @return  Whether or not the search was successful.
 */
int	    search(const char *root, const Settings *settings) {
    DIR * dir = opendir(root);
    struct dirent * read;
    int numberFiles = 0;
    char * path = NULL;
    if (dir == NULL) { // cant open
        perror("opendir() error");
        return EXIT_FAILURE;
    }
    while ((read = readdir(dir)) != NULL){
        numberFiles++;
        sprintf(path, "%s/%s", root, read->d_name); 
        // skip '.' and '..'
        if (streq(read->d_name, ".") || streq(read->d_name, "..")) continue;         if (!filter(path, settings)) { // include
            execute(path, settings);
            if (read->d_type == DT_DIR)
                search(path, settings);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

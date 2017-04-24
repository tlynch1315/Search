/* search.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

/**
 * Recursively search through the provided root directory
 * @param   root        Path to directory
 * @param   settings    Settings structure
 * @return  Whether or not the search was successful.
 */
int	    search(const char *root, const Settings *settings) {
    DIR * dir = opendir(root);
    if(dir){
        struct dirent * read;
        while ((read = readdir(dir)) != NULL){
            struct stat s;
            lstat(read->d_name, &s);

            if(streq(read->d_name, ".")){
                if(!filter(root, settings))
                    execute(root, settings);
            }
            else if(streq(read->d_name, "..")){
                continue;
            }
            else{
                char new_path[strlen(root) + strlen(read->d_name) + 2];
                sprintf(new_path, "%s/%s", root, read->d_name);

                if(read->d_type == DT_DIR)
                    search(new_path, settings);
                else
                    if(!filter(new_path, settings))
                        execute(new_path, settings);
            }
        }
    }
    else{
        if(!filter(root, settings))
            execute(root, settings);
        closedir(dir);
        return EXIT_FAILURE;
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

/* utilities.c */

#include "search.h"

#include <errno.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Test whether or not a directory is empty.
 * @param   path        Path to directory.
 * @return  Whether or not a directory is empty.
 */
bool        is_directory_empty(const char *path) {
    DIR * dir = opendir(path);
    struct dirent * read;
    if (dir == NULL) {// cant open
        perror("opendir() error"); // error if cannot open
        return false;
    }
    while ((read = readdir(dir)) != NULL) {
        if(read->d_type != DT_DIR){
            closedir(dir);
            return false;
        }
        else if(strcmp(read->d_name, "." )&& strcmp(read->d_name, "..")){
            closedir(dir);
            return false;
        }
    }
    closedir(dir);
    return true;
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t      get_mtime(const char *path) {
    struct stat info;
    int returnVal = lstat(path, &info);
    if (returnVal == -1) { // error
        perror("lstat() error");
        return 0;
    }
    return info.st_mtime;
}


/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

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
    if(!dir){
        perror("opendir() error"); // error if cannot open
        return false;
    }
    struct direct *d;
    int files = 0;
    for(d = readdir(dir); d; d = readdir(dir)){
        files++;
    }
    closedir(dir);
    if(files <= 2){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t      get_mtime(const char *path) {
    struct stat info;
    if(!lstat(path, &info))
        return info.st_mtime;
    else return 0;
}


/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

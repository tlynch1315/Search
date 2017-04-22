/* filter.c */

#include "search.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <unistd.h>

#include<stdlib.h>

/**
 * Test whether or not the given path should be filtered out of the output.
 * @param   path        Path to file or directory.
 * @param   settings    Settings structure.
 * @return  Whether or not the path should be excluded from the output (true to
 * exclude, false to include).
 */
bool        filter(const char *path, const Settings *settings) {
    struct stat s;
    lstat(path, &s);

    if(settings->type){     // tests if it is a file
        if(settings->type == 'f' && !S_ISREG(s.st_mode)){
            return true;    // returning 0 for type means it is a file, so if it
                            // is a file then it will be false
        }
        else if(settings->type == 'd' && !S_ISREG(s.st_mode)){
            return true;
        }
    }

    if(settings->empty){
        if(S_ISDIR(s.st_mode)){
            if(!is_directory_empty(path))
                return true;
        }
        else if(S_ISREG(s.st_mode)){
            if(s.st_size != 0)
                return true;
        }
        else return true;
    }

    if(settings->access && access(path, settings->access) != 0) return true;

    if(settings->name){
        char *name = strdup(path);
        if(fnmatch(settings->name, basename(name), 0) == FNM_NOMATCH){
            free(name);
            return true;
        }
        free(name);
    }

    if(settings->path){
        char *name = strdup(path);
        if(fnmatch(settings->path, name, 0)){
            free(name);
            return true;
        }
        free(name);

    if(settings->perm){
        int permissions = s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
        if(settings->perm != permissions){
            return true;
        }
    }
    if(settings->newer && settings->newer >= get_mtime(path))
        return true;

    if(settings->uid != -1 && s.st_uid != settings->uid)
        return true;
    if(settings->gid != -1 && s.st_gid != settings->gid)
        return true;
    }
    return false;

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

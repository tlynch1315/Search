/* filter.c */

#include "search.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <unistd.h>

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
    if(settings->type) { // type flag is used
        if (settings->type == 'f' && !S_ISREG(s.st_mode))
            return true; // exclude if type is f and its not a file
        if (settings->type == 'd' && !S_ISDIR(s.st_mode))
            return true; // exlcude if type is d and not directory
    }

    if (settings->empty) { // empty flag is used
        if (S_ISDIR(s.st_mode)){
            if (!is_directory_empty(path)) return true; // direct not empty
        }
        else if (S_ISREG(s.st_mode)){
            if(s.st_size != 0) return true; //size not 0
        }
        else return true;
       
    }
     
    // access flag is used but no acces for file is given
    if (settings->access && access(path, settings->access) != 0) return true;
    
    if (settings->name) { //name flag is used
        const char * temp = strdup(path);
        if (fnmatch(settings->name, basename(temp), 0) == FNM_NOMATCH) {
            free(temp);
            return true;
        }
        free(temp);
    }

    if (settings->path) { //path flag is used
        const char * temp = strdup(path);
        if (fnmatch(settings->path, temp, 0) == FNM_NOMATCH ){
            free(temp);
            return true;
        }
        free(temp);
    }
    
    if (settings->perm) { // perm flag is used
        int permissions = s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
        if (settings->perm != permissions) return true;
    }

    // newer flags handeling
    if (settings->newer && settings->newer >= get_mtime(path)) return true;
    
    // uid
    if (settings->uid != -1 && s.st_uid != settings->uid) return true;
    
    // gid
    if (settings->gid != -1 && s.st_gid != settings->gid) return true;
    
    // if everything else passes
    return false;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

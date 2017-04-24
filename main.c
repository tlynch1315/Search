/* driver.c */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

/* Functions */

void	    usage(const char *program_name, int status) {
    fprintf(stderr, "Usage: %s PATH [OPTIONS] [EXPRESSION]\n", program_name);
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "    -executable     File is executable or directory is searchable to user\n");
    fprintf(stderr, "    -readable       File readable to user\n");
    fprintf(stderr, "    -writable       File is writable to user\n\n");
    fprintf(stderr, "    -type [f|d]     File is of type f for regular file or d for directory\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -name  pattern  Base of file name matches shell pattern\n");
    fprintf(stderr, "    -path  pattern  Path of file matches shell pattern\n\n");
    fprintf(stderr, "    -perm  mode     File's permission bits are exactly mode (octal)\n");
    fprintf(stderr, "    -newer file     File was modified more recently than file\n\n");
    fprintf(stderr, "    -uid   n        File's numeric user ID is n\n");
    fprintf(stderr, "    -gid   n        File's numeric group ID is n\n");
    fprintf(stderr, "\nExpressions:\n\n");
    fprintf(stderr, "    -print          Display file path (default)\n");
    fprintf(stderr, "    -exec cmd {} ;  Execute command on path\n");
    exit(status);
}

Settings settings = {
    .access = 0,
    .uid    = -1,
    .gid    = -1,
};

/* Main Execution */

int	    main(int argc, char *argv[]) {

    /* Parse command line arguments*/
    int argind = 1;
    char *program_name = NULL;
    program_name = argv[0];
    char * root = argv[argind++];
    if(argc == 1)
        usage(program_name, 1);
    if(strcmp(root, "easter") == 0){
        puts("Congratulations, you found the easter egg, that will be one guru point please :)\n");
        return EXIT_SUCCESS;
    }

    while(argind < argc  && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
        char *arg = argv[argind++];
        if(strcmp(arg, "-executable") == 0)
            settings.access |= X_OK;
        if(strcmp(arg, "-readable") == 0)
            settings.access |= R_OK;
        if(strcmp(arg, "-writable") == 0)
            settings.access |= W_OK;
        if(strcmp(arg, "-type") == 0){
            char c = argv[argind++][0];
            settings.type = c;
        }
        if(strcmp(arg, "-empty") == 0)
            settings.empty = true;
        if(strcmp(arg, "-name") == 0)
            settings.name = argv[argind++];
        if(strcmp(arg, "-path") == 0)
            settings.path = argv[argind++];
        if(strcmp(arg, "-perm") == 0){
            char *extra;
            char *input = argv[argind++];
            settings.perm = strtoul(input, &extra, 8);
        }

        if(strcmp(arg, "-newer") == 0){
            char *new = argv[argind++];
            time_t time = get_mtime(new);
            settings.newer = time;
        }
        if(strcmp(arg, "-uid") == 0){
            char *n = argv[argind++];
            settings.uid = atoi(n);
        }
        if(strcmp(arg, "-gid") == 0){
            char *n = argv[argind++];
            settings.gid = atoi(n);
        }
        if(strcmp(arg, "-print") == 0){
            settings.print = true;
        }
        if(strcmp(arg, "-exec") == 0){
            settings.exec_argv = &argv[argind++];
            int count = 1;
            if(argind >= argc){
                fprintf(stderr, "Error: invalid use of exec flag\n");
                usage(program_name, 1);
            }
            while(!streq(argv[argind++], ";")){
                count++;
                if (argind >= argc){
                    fprintf(stderr, "Error: invalid use of exec flag\n");
                    usage(program_name, 1);
                }
            }
            settings.exec_argc = count;
        }
    }
    search(root, &settings);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "server.h"
#include "globals.h"

int main(int argc, char *argv[]){
    int ch, background = 0;
    char port[10] = "8080";
    pid_t pid;

    struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {"log", required_argument, 0, 'l'},
        {"statistics", required_argument, 0, 's'},
        {"background", no_argument, 0, 'b'},
        {"root", required_argument, 0, 'r'},
    };
    
    while ((ch = getopt_long(argc, argv, "p:l:s:br:", long_options, NULL)) != -1) {
        switch (ch) {
            case 'p':
                strcpy(port, optarg);
                break;
            case 'l':
                strcpy(log_file, optarg);
                break;
            case 's':
                strcpy(statistics_file, optarg);
                break;
            case 'b':
                background = 1;
                break;
            case 'r':
                strcpy(root_path, optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s [-p PORTA] [-l LOGFILE] [-s STATFILE] [-b] [-r ROOTPATH]\n", argv[0]);
                exit(-1);
        }
    }
    
    if (background){
        if((pid = fork()) > 0){
            exit(0);
        }
    }
    
    server(port);

    return 0;
}
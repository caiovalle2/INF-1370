#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "globals.h"

extern int socket_fd;
extern sem_t semaphore;
extern char log_file[50], statistics_file[50], root_path[50];

void close_server(int signal){
    FILE *file_s;
    char buffer_s[100];

    close(socket_fd);
    sem_destroy(&semaphore);
    sem_destroy(&semaphore_l);

    printf("Servidor finalizado com sucesso !\n");
    
    if (statistics_file[0] != '\0'){
        if((file_s = fopen(statistics_file, "w")) == NULL){
        printf("Erro ao abrir arquivo de estatistica\n");
        exit(-1);
        }
        snprintf(buffer_s, sizeof(buffer_s), "Numero de arquivos:\n"
                                            "HTML: %d\n"
                                            "Texto: %d\n"
                                            "Image: %d\n", fc.html, fc.txt, fc.image);
        
        fprintf(file_s, "%s", buffer_s);

        fclose(file_s);
    }


    exit(0);
}
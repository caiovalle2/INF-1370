#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>
#include "globals.h"
#include "handleclient.h"
#include "closeserver.h"
#include "consumer.h"

char log_file[50], statistics_file[50], root_path[50], buffer_l[10000];

fileCounter fc;
int socket_fd;
sem_t semaphore, semaphore_l;

void server(char *port){
    struct addrinfo hints, *addrHost;
    int *client_fd;
    pid_t pid = getpid();
    unsigned len_client;
    tEndereco addr_client;
    
    fc.html = 0;
    fc.image = 0;
    fc.txt = 0;

    sem_init(&semaphore, 0, 1);
    sem_init(&semaphore_l, 0, 1);

    if(signal(SIGUSR1, close_server) == SIG_ERR){
        printf("Erro a criar sinal! \n");
        exit(-1);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_ADDRCONFIG | AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(NULL, port, &hints, &addrHost) != 0){
        printf("Nao obtive informacoes sobre o servidor \n");
        exit(-1);
    }

    socket_fd = socket(addrHost->ai_family, addrHost->ai_socktype, addrHost->ai_protocol);

    if (socket_fd == -1){
        printf("Erro na criacao do socket \n");
        exit(-1);
    }
    
    if (bind(socket_fd, addrHost->ai_addr, addrHost->ai_addrlen) == -1){
        printf("Erro ao vincular o socket \n");
        exit(-1);
    }

    if (listen(socket_fd, MAXLISTEN) == -1){
        printf("Erro no listen \n");
        exit(-1);
    }
    
    printf("Servidor inicializado !\n");
    printf("Para encerrar use o comando: kill -SIGUSR1 %d\n", pid);

    if (log_file[0] != '\0'){
        pthread_t tid;
        if (pthread_create(&tid, NULL, consumer, NULL) != 0){
            printf("Erro ao criar thread \n");
            exit(-1);
        }
        pthread_detach(tid);
    }
    
    while(1){
        len_client = sizeof(addr_client);

        client_fd = malloc(sizeof(int));
        if (client_fd == NULL){
            perror("malloc");
            exit(-1);
        }

        *client_fd = accept(socket_fd, (struct sockaddr *)&addr_client, &len_client);

        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, (void*)client_fd) != 0){
            printf("Erro ao criar thread \n");
            exit(-1);
        }
        pthread_detach(tid);
    }
    
}
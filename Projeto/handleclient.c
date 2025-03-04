#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "globals.h"


void *handle_client(void *param){
    int client_fd = *((int *) param), bytes_requested;
    FILE *file;
    char dir[200], buffer_request[10000], buffer_response[10000], buffer[1000], type, content_type[20], msg_l[1000], time_str[50];
    time_t current_time;
    struct tm local_time;
    
    strcpy(dir, root_path);
    //Leitura da requisição
    if((bytes_requested = read(client_fd, buffer_request, sizeof(buffer_request))) >= 0){
        int i = 0, x = strlen(dir);

        //Pegando o dir do arquivo requisitado
        while (buffer_request[i] != '/'){
            i++;
        }
        x == 0 ? i++ : i;
        while(buffer_request[i] != ' '){
            if (buffer_request[i] == '.'){
                type = buffer_request[i+1];
            }
            dir[x++] = buffer_request[i];
            i++;
        }
        dir[x] = '\0';

        //Criando o content-type
        sem_wait(&semaphore);
        switch(type){
            case 'h':
                fc.html++;
                strcpy(content_type, "text/html");
                break;
            case 'p':
                fc.image++;
                strcpy(content_type, "image/png");
                break;
            case 'j':
                fc.image++;
                strcpy(content_type, "image/jpeg");
                break;
            case 't':
                fc.txt++;
                strcpy(content_type, "text/plain");
                break;
        }
        
        time(&current_time);
        localtime_r(&current_time, &local_time);
        asctime_r(&local_time, time_str);
        
        //Criando a resposta
        file = fopen(dir, "r");

        if (file == NULL){
            strcpy(buffer_response, "HTTP/1.1 404 NOT FOUND\r\n"
                                    "Content-Type: text/plain\r\n\r\n"
                                    "404 Not Found");
                                    
            snprintf(msg_l, sizeof(msg_l),"Arquivo %s não encontrado\n", dir);
        }
        else if(fread(buffer, 1, sizeof(buffer), file) == -1) {
            fclose(file);
            snprintf(msg_l, sizeof(msg_l),"Erro de leitura do arquivo %s\n", dir);
        }
        else {
            fclose(file);
            snprintf(buffer_response, sizeof(buffer_response), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: %s\r\n\r\n"
             "%s", content_type, buffer);
            snprintf(msg_l, sizeof(msg_l),"%s %s", dir, time_str);
        }  

        //Envio da resposta
        if (write(client_fd, buffer_response, strlen(buffer_response)) == -1){
            snprintf(msg_l, sizeof(msg_l),"Erro no envio da resposta ao cliente - %s\n", dir);            
        }
        
        sem_post(&semaphore);
    
    }

    sem_wait(&semaphore_l);
    strcat(buffer_l, msg_l);
    sem_post(&semaphore_l);

    close(client_fd);
    free(param);

    return NULL;
}
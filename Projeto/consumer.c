#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

void *consumer(){
    FILE *file_l;

    while(1){
        sem_wait(&semaphore_l);
        if (buffer_l[0] != '\0'){
            if ((file_l = fopen(log_file, "a")) == NULL){
                continue;
            }
            fprintf(file_l, "%s", buffer_l);
            buffer_l[0] = '\0';
            fclose(file_l);
        }
        sem_post(&semaphore_l);
    }
}
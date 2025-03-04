#define MAXLISTEN 100000
#include <netdb.h>
#include <semaphore.h>

typedef struct {
    int html, image, txt;
} fileCounter;

typedef union {
    struct sockaddr_in cliente4;
    struct sockaddr_in6 cliente6;
} tEndereco;

extern fileCounter fc;
extern sem_t semaphore, semaphore_l;
extern char log_file[50], statistics_file[50], root_path[50], buffer_l[10000];
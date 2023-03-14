#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <ctype.h>
 
#define TRUE   1
#define FALSE  0
#define PORT 5000
#define LG_MESSAGE 256



struct CLIENT {
    int socket;
    struct CLIENT *next;
};


struct COULEUR {
    int R;
    int G;
    int B;
};

typedef struct CLIENT Client;
typedef struct COULEUR couleur;


void add_client(Client **head, int socket);
void remove_client(Client **head, int socket);
void print_clients(Client *head);

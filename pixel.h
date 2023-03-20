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
#define NB_LIGNE 5 //hauteur
#define NB_COLONNE 5 //largeur
#define TAILLE_MAX_CHAINE 20



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
void initMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]);
void afficheMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]);
char* intToBinary(int n,int decal,char *binary);
char binary_to_base64(char* binary, char* base64_output);
char * rgbToBinary(int r, int g, int b);
void setPixel(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE], int hauteur, int largeur, int R, int G, int B);
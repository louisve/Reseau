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
#include <getopt.h>
#include <math.h>
 
 
#define TRUE   1
#define FALSE  0
#define PORT 5000
#define LG_MESSAGE 100000
#define NB_COLONNE 80
#define NB_LIGNE 40
#define TAILLE_MAX_CHAINE 20
#define PIXEL_PER_MINUTE_MAX 12 
#define VERSION 1


struct CLIENT {
    int socket;
    struct CLIENT *next;
};


typedef struct CLIENT Client;
typedef struct COULEUR couleur;


void add_client(Client **head, int socket);
void remove_client(Client **head, int socket);
void print_clients(Client *head);
void initMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]);
void afficheMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]);
char* intToBinary(int n,int decal,char *binary);
void binary_to_base64(char* binary, char* base64_output);
char * rgbToBinary(int r, int g, int b);
char* base64_to_binary(char* base64_string);
void binary_to_rgb(char* binary_string, int* R, int* G, int* B);
int setPixel(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE], int hauteur, int largeur, char *base64);
int VerifBase64(char *base64);

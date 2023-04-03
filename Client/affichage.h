#include "Client.h"


// #include <SDL2/SDL.h>


// // dimensions de la fenêtre
// #define SCREEN_WIDTH 1920
// #define SCREEN_HEIGHT 1080

// // dimensions du quadrillage

// #define GRID_MAX_WIDTH 1000
// #define GRID_MAX_HEIGHT 800

// #define COTE_PALETTE 187
// #define START_X_PALLETTE 1100
// #define START_Y_PALETTE 200

// //Dimensions bouton
// #define START_X_BOUTON 1287
// #define START_Y_BOUTON 650
// #define LARGEUR_BOUTON 374
// #define HAUTEUR_BOUTON 100

#define NB_LIGNE 40
#define NB_COLONNE 80
#define TAILLE_MAX_CHAINE 20





// void drawGrid(SDL_Renderer* renderer, SDL_Color color);
// void selectCase(SDL_Renderer* renderer, int x, int y, SDL_Color color, int* i, int* j);
// void palette(SDL_Renderer* renderer);
// char* selectCouleur(int x, int y, char* chaine64);
// int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
// int affichage(char* chaine64,int* i, int* j, int envoie,char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]);
// char* intToBinary(int n,int decal,char *binary);
// void binary_to_base64(char* binary, char* base64_output);
// char * rgbToBinary(int r, int g, int b);
// void bouton(SDL_Renderer* renderer, SDL_Color color);
// void colorCase(SDL_Renderer* renderer, int i, int j,SDL_Color color);
void matriceTerminal(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]);
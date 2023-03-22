#include "Client.h"

// dimensions de la fenêtre
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

// dimensions du quadrillage

#define GRID_MAX_WIDTH 1000
#define GRID_MAX_HEIGHT 800

#define COTE_PALETTE 187
#define START_X_PALLETTE 1100
#define START_Y_PALETTE 100

void drawGrid(SDL_Renderer* renderer, SDL_Color color);
void colorCell(SDL_Renderer* renderer, int x, int y, SDL_Color color);
void palette(SDL_Renderer* renderer);
char* selectCouleur(int x, int y, char* chaine64);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
void affichage(char* chaine64);
char* intToBinary(int n,int decal,char *binary);
void binary_to_base64(char* binary, char* base64_output);
char * rgbToBinary(int r, int g, int b);
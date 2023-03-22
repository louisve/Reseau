#include "affichage.h"

// fonction qui dessine la grille
void drawGrid(SDL_Renderer* renderer, SDL_Color color){
    int GRID_WIDTH = GRID_MAX_WIDTH / NB_COLONNE;
    int GRID_HEIGHT = GRID_MAX_HEIGHT / NB_LIGNE;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // dessine les lignes verticales
    for(int i = 0; i <= GRID_MAX_WIDTH ; i += GRID_WIDTH)
    {
        SDL_RenderDrawLine(renderer, i, 0, i, GRID_MAX_HEIGHT);
    }
    
    // dessine les lignes horizontales
    for(int j = 0; j <= GRID_MAX_HEIGHT; j += GRID_HEIGHT)
    {
        SDL_RenderDrawLine(renderer, 0, j, GRID_MAX_WIDTH, j);
    }
}

// fonction qui colorie la case sélectionnée en rouge
void colorCell(SDL_Renderer* renderer, int x, int y, SDL_Color color){
    int GRID_WIDTH = GRID_MAX_WIDTH / NB_COLONNE;
    int GRID_HEIGHT = GRID_MAX_HEIGHT / NB_LIGNE;
    // calcule les indices de la case sélectionnée
    int i = x / GRID_WIDTH;
    int j = y / GRID_HEIGHT;
    
    // calcule les coordonnées de la case sélectionnée
    int x1 = i * GRID_WIDTH;
    int y1 = j * GRID_HEIGHT;
    int x2 = x1 + GRID_WIDTH - 1;
    int y2 = y1 + GRID_HEIGHT - 1;
    
    // dessine un rectangle rouge dans la case sélectionnée
    SDL_Rect rect = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

// void initCases(SDL_Renderer* renderer, char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]){

//     for(int i = 0; i <= NB_LIGNE, i++){
//         for(int j = 0, j <= NB_COLONNE, j++){
//             colorCell(renderer, i, j,color);
//         }
//     }
// }

void palette(SDL_Renderer* renderer){

    SDL_Rect case1 = {START_X_PALLETTE,START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderFillRect(renderer, &case1);

    SDL_Rect case2 = {START_X_PALLETTE+COTE_PALETTE,START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    SDL_RenderFillRect(renderer, &case2);

    SDL_Rect case3 = {START_X_PALLETTE+(2*COTE_PALETTE),START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderFillRect(renderer, &case3);

    SDL_Rect case4 = {START_X_PALLETTE+(3*COTE_PALETTE),START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderFillRect(renderer, &case4);

    SDL_Rect case5 = {START_X_PALLETTE,START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 255,0,255,255);
    SDL_RenderFillRect(renderer, &case5);

    SDL_Rect case6 = {START_X_PALLETTE+(COTE_PALETTE),START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 0,255,255,255);
    SDL_RenderFillRect(renderer, &case6);

    SDL_Rect case7 = {START_X_PALLETTE+(2*COTE_PALETTE),START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 255,255,0,255);
    SDL_RenderFillRect(renderer, &case7);

    SDL_Rect case8 = {START_X_PALLETTE+(3*COTE_PALETTE),START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &case8);

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    for (int i = START_Y_PALETTE; i < START_Y_PALETTE+(3*COTE_PALETTE); i += COTE_PALETTE){
        SDL_RenderDrawLine(renderer, START_X_PALLETTE, i, START_X_PALLETTE+(4*COTE_PALETTE), i);
    }
    for (int i = START_X_PALLETTE; i < START_X_PALLETTE+(5*COTE_PALETTE); i += COTE_PALETTE){
        SDL_RenderDrawLine(renderer, i, START_Y_PALETTE, i, START_Y_PALETTE+(2*COTE_PALETTE));
    }
}

char* selectCouleur(int x, int y, char* chaine64){

    if(x >= START_X_PALLETTE && x <= START_X_PALLETTE+COTE_PALETTE && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
        char * chaine = rgbToBinary(0,0,255);
        //printf("bleu\n");
        binary_to_base64(chaine,chaine64);
    }

    else if(x >= START_X_PALLETTE+COTE_PALETTE && x <= START_X_PALLETTE+(2*COTE_PALETTE) && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
        char * chaine = rgbToBinary(0,255,0);
        binary_to_base64(chaine,chaine64);
        //printf("vert\n");
    }

    else if(x >= START_X_PALLETTE+(2*COTE_PALETTE) && x <= START_X_PALLETTE+(3*COTE_PALETTE) && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
        char * chaine = rgbToBinary(255,0,0);
        binary_to_base64(chaine,chaine64);
        //printf("rouge\n");
    }

    else if(x >= START_X_PALLETTE+(3*COTE_PALETTE) && x <= START_X_PALLETTE+(4*COTE_PALETTE) && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
        char * chaine = rgbToBinary(0,0,0);
        binary_to_base64(chaine,chaine64);
        //printf("noir\n");
    }

    else if(x >= START_X_PALLETTE && x <= START_X_PALLETTE+COTE_PALETTE && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
        char * chaine = rgbToBinary(255,0,255);
        binary_to_base64(chaine,chaine64);
        //printf("magenta\n");
    }

    else if(x >= START_X_PALLETTE+COTE_PALETTE && x <= START_X_PALLETTE+(2*COTE_PALETTE) && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
        char * chaine = rgbToBinary(0,255,255);
        binary_to_base64(chaine,chaine64);
        //printf("cyan\n");
    }

    else if(x >= START_X_PALLETTE+(2*COTE_PALETTE) && x <= START_X_PALLETTE+(3*COTE_PALETTE) && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
        char * chaine = rgbToBinary(255,255,0);
        binary_to_base64(chaine,chaine64);
        //printf("jaune\n");
    }

    else if(x >= START_X_PALLETTE+(3*COTE_PALETTE) && x <= START_X_PALLETTE+(4*COTE_PALETTE) && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
        char * chaine = rgbToBinary(255,255,255);
        binary_to_base64(chaine,chaine64);
        //printf("blanc\n");
    }


return chaine64;
}

int setWindowColor(SDL_Renderer *renderer, SDL_Color color){
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0){
        return -1;
    }
        
    if(SDL_RenderClear(renderer) < 0){
        return -1;
    }
        
    return 0;  
}

void affichage(char* chaine64){
    // initialise SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // crée une fenêtre
    SDL_Window* window = SDL_CreateWindow("PIXEL WAR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    // crée un rendu de la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //Couleurs 
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color noir = {0, 0, 0, 255};
    SDL_Color rouge = {255,0,0,255};

    // dessine le fond en noir
    setWindowColor(renderer, blanc);
    SDL_RenderClear(renderer);
        
    // dessine la grille
    drawGrid(renderer,noir);

    palette(renderer);
    SDL_RenderPresent(renderer);
    // boucle principale
    SDL_Event event;
    int running = 1;
    while(running)
    {
        // gère les événements
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                // ferme la fenêtre si on appuie sur la croix
                case SDL_QUIT:
                    running = 0;
                    break;
                
                // colorie la case si on clique dessus
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT )
                    {
                        if(event.button.x <= GRID_MAX_WIDTH && event.button.y <= GRID_MAX_HEIGHT){
                            colorCell(renderer, event.button.x, event.button.y,rouge);
                        }
                        else if(event.button.x <= START_X_PALLETTE + (4*COTE_PALETTE) && event.button.y <= START_Y_PALETTE+(2*COTE_PALETTE) && event.button.x >= START_X_PALLETTE && event.button.y >= START_Y_PALETTE){
                            
                            selectCouleur(event.button.x, event.button.y, chaine64);
                            //printf("La couleur  choisit est : %s\n", chaine64);
                        }
                    }

                    break;
            }
        }
        
        
        
        // met à jour l'affichage
        SDL_RenderPresent(renderer);
    }
    
    // nettoie la mémoire
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

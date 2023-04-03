#include "affichage.h"


//Pour afficher la matrice en couleur dans le terminal grace aux codes retour ANSI
void matriceTerminal(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]){
    
    for (int i = 0; i < NB_LIGNE; i++) {
        for (int j = 0; j < NB_COLONNE; j++) {
            if(strcmp("AAD/",matrice[i][j]) == 0){
                printf("\033[44m  \033[0m");
            }
            else if(strcmp("AP8A\0",matrice[i][j]) == 0){
                printf("\033[42m  \033[0m");
            }
            else if(strcmp("/wAA\0",matrice[i][j]) == 0){
                printf("\033[41m  \033[0m");
            }
    
            else if(strcmp("AAAA\0",matrice[i][j]) == 0){
                 printf("\033[40m  \033[0m");
            }
            else if(strcmp("/wD/\0",matrice[i][j]) == 0){
                printf("\033[45m  \033[0m");
            }
            else if(strcmp("AP//\0",matrice[i][j]) == 0){
                printf("\033[46m  \033[0m");
            }
            else if(strcmp("//8A\0",matrice[i][j]) == 0){
                printf("\033[43m  \033[0m");
            }
            else if(strcmp("////\0",matrice[i][j]) == 0){
                
                printf("\033[47m  \033[0m");
            }
            
        }
        printf("\n");
    }
   
}  

//Pour afficher la liste des commandes utilisables dans le terminal
void listeCommandes(){
    printf("---------------------------------------------------------------------------------------------\n");              
    printf("| Tapez l'une des commandes suivantes          |        Couleurs en base64 disponibles      |\n");
    printf("---------------------------------------------------------------------------------------------\n");              
    printf("|  /getMatrix                                  |                                            |\n");
    printf("|  /getSize                                    |    \033[30mNoir :    AAAA\033[0m   |   \033[35mMagenta : /wd/\033[0m     |\n");
    printf("|  /getLimits                                  |    \033[34mBleu :    AAD/\033[0m   |   \033[36mCyan :    AP//\033[0m     |\n");
    printf("|  /getWaitTime                                |    \033[31mRouge :   /wAA\033[0m   |   \033[33mJaune :   //8A\033[0m     |\n");
    printf("|  /getVersion                                 |    \033[37mBlanc :   ////\033[0m   |   \033[32mVert:     AP8A\033[0m     |\n");
    printf("|  /setPixel lignexcolonne couleur(en base 64) |                                            |\n");
    printf("---------------------------------------------------------------------------------------------\n");              
        
}


//PARTIE SDL : NOUS N'AVONS PAS EU LE TEMPS DE L'IMPLÉMENTER CORRECTEMENT
    // // fonction qui dessine la grille
    // void drawGrid(SDL_Renderer* renderer, SDL_Color color){
    //     int GRID_WIDTH = round(GRID_MAX_WIDTH / NB_COLONNE);
    //     int GRID_HEIGHT = round(GRID_MAX_HEIGHT / NB_LIGNE);
    //     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    //     // dessine les lignes verticales
    //     for(int i = 0; i <= NB_COLONNE*GRID_WIDTH ; i += GRID_WIDTH)
    //     {
    //         SDL_RenderDrawLine(renderer, i, 0, i, NB_LIGNE*GRID_HEIGHT);
    //     }
        
    //     // dessine les lignes horizontales
    //     for(int j = 0; j <= NB_LIGNE*GRID_HEIGHT ; j += GRID_HEIGHT)
    //     {
    //         SDL_RenderDrawLine(renderer, 0, j, NB_COLONNE*GRID_WIDTH, j);
    //     }
    // }

    // // fonction qui entoure la case selctionnée en noir
    // void selectCase(SDL_Renderer* renderer, int x, int y, SDL_Color color, int* i, int* j){
    //     int GRID_WIDTH = GRID_MAX_WIDTH / NB_COLONNE;
    //     int GRID_HEIGHT = GRID_MAX_HEIGHT / NB_LIGNE;
    //     // calcule les indices de la case sélectionnée
    //     *i = x / GRID_WIDTH;
    //     *j = y / GRID_HEIGHT;
        
    //     // calcule les coordonnées de la case sélectionnée
    //     int x1 = *i * GRID_WIDTH;
    //     int y1 = *j * GRID_HEIGHT;
    //     int x2 = x1 + GRID_WIDTH ;
    //     int y2 = y1 + GRID_HEIGHT;
        
    //     // dessine un rectangle noir dans la case sélectionnée
    //     SDL_Rect rect = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
    //     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    //     SDL_RenderDrawRect(renderer, &rect);
    // }

    // void colorCase(SDL_Renderer* renderer, int i, int j,SDL_Color color){
    
    //     int GRID_WIDTH = GRID_MAX_WIDTH / NB_COLONNE;
    //     int GRID_HEIGHT = GRID_MAX_HEIGHT / NB_LIGNE;
    //     // calcule les indices de la case sélectionnée
    //     int x = j* GRID_WIDTH;
    //     int y = i * GRID_HEIGHT;
        
    //     // dessine un rectangle dans la case i,j
    //     SDL_Rect rect = {x, y, GRID_WIDTH , GRID_HEIGHT };
    //     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    //     SDL_RenderFillRect(renderer,&rect);
    // }

    // void palette(SDL_Renderer* renderer){

    //     SDL_Rect case1 = {START_X_PALLETTE,START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    //     SDL_RenderFillRect(renderer, &case1);

    //     SDL_Rect case2 = {START_X_PALLETTE+COTE_PALETTE,START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    //     SDL_RenderFillRect(renderer, &case2);

    //     SDL_Rect case3 = {START_X_PALLETTE+(2*COTE_PALETTE),START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    //     SDL_RenderFillRect(renderer, &case3);

    //     SDL_Rect case4 = {START_X_PALLETTE+(3*COTE_PALETTE),START_Y_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    //     SDL_RenderFillRect(renderer, &case4);

    //     SDL_Rect case5 = {START_X_PALLETTE,START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 255,0,255,255);
    //     SDL_RenderFillRect(renderer, &case5);

    //     SDL_Rect case6 = {START_X_PALLETTE+(COTE_PALETTE),START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 0,255,255,255);
    //     SDL_RenderFillRect(renderer, &case6);

    //     SDL_Rect case7 = {START_X_PALLETTE+(2*COTE_PALETTE),START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 255,255,0,255);
    //     SDL_RenderFillRect(renderer, &case7);

    //     SDL_Rect case8 = {START_X_PALLETTE+(3*COTE_PALETTE),START_Y_PALETTE+COTE_PALETTE,COTE_PALETTE,COTE_PALETTE};
    //     SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    //     SDL_RenderFillRect(renderer, &case8);

    //     SDL_SetRenderDrawColor(renderer,0,0,0,255);
    //     for (int i = START_Y_PALETTE; i < START_Y_PALETTE+(3*COTE_PALETTE); i += COTE_PALETTE){
    //         SDL_RenderDrawLine(renderer, START_X_PALLETTE, i, START_X_PALLETTE+(4*COTE_PALETTE), i);
    //     }
    //     for (int i = START_X_PALLETTE; i < START_X_PALLETTE+(5*COTE_PALETTE); i += COTE_PALETTE){
    //         SDL_RenderDrawLine(renderer, i, START_Y_PALETTE, i, START_Y_PALETTE+(2*COTE_PALETTE));
    //     }
    // }

    // char* selectCouleur(int x, int y, char* chaine64){

    //     if(x >= START_X_PALLETTE && x <= START_X_PALLETTE+COTE_PALETTE && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
    //         char * chaine = rgbToBinary(0,0,255);
    //         //printf("bleu\n");
    //         binary_to_base64(chaine,chaine64);
    //     }

    //     else if(x >= START_X_PALLETTE+COTE_PALETTE && x <= START_X_PALLETTE+(2*COTE_PALETTE) && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
    //         char * chaine = rgbToBinary(0,255,0);
    //         binary_to_base64(chaine,chaine64);
    //         //printf("vert\n");
    //     }

    //     else if(x >= START_X_PALLETTE+(2*COTE_PALETTE) && x <= START_X_PALLETTE+(3*COTE_PALETTE) && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
    //         char * chaine = rgbToBinary(255,0,0);
    //         binary_to_base64(chaine,chaine64);
    //         //printf("rouge\n");
    //     }

    //     else if(x >= START_X_PALLETTE+(3*COTE_PALETTE) && x <= START_X_PALLETTE+(4*COTE_PALETTE) && y >= START_Y_PALETTE && y <= START_Y_PALETTE+COTE_PALETTE){
    //         char * chaine = rgbToBinary(0,0,0);
    //         binary_to_base64(chaine,chaine64);
    //         //printf("noir\n");
    //     }

    //     else if(x >= START_X_PALLETTE && x <= START_X_PALLETTE+COTE_PALETTE && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
    //         char * chaine = rgbToBinary(255,0,255);
    //         binary_to_base64(chaine,chaine64);
    //         //printf("magenta\n");
    //     }

    //     else if(x >= START_X_PALLETTE+COTE_PALETTE && x <= START_X_PALLETTE+(2*COTE_PALETTE) && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
    //         char * chaine = rgbToBinary(0,255,255);
    //         binary_to_base64(chaine,chaine64);
    //         //printf("cyan\n");
    //     }

    //     else if(x >= START_X_PALLETTE+(2*COTE_PALETTE) && x <= START_X_PALLETTE+(3*COTE_PALETTE) && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
    //         char * chaine = rgbToBinary(255,255,0);
    //         binary_to_base64(chaine,chaine64);
    //         //printf("jaune\n");
    //     }

    //     else if(x >= START_X_PALLETTE+(3*COTE_PALETTE) && x <= START_X_PALLETTE+(4*COTE_PALETTE) && y >= START_Y_PALETTE+COTE_PALETTE && y <= START_Y_PALETTE+(2*COTE_PALETTE)){
    //         char * chaine = rgbToBinary(255,255,255);
    //         binary_to_base64(chaine,chaine64);
    //         //printf("blanc\n");
    //     }


    // return chaine64;
    // }

    // int setWindowColor(SDL_Renderer *renderer, SDL_Color color){
    //     if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0){
    //         return -1;
    //     }
            
    //     if(SDL_RenderClear(renderer) < 0){
    //         return -1;
    //     }
            
    //     return 0;  
    // }


    // int affichage(char* chaine64,int* i, int* j, int envoie,char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]){
    //     // initialise SDL
    //     SDL_Init(SDL_INIT_VIDEO);
        
    //     // crée une fenêtre
    //     SDL_Window* window = SDL_CreateWindow("PIXEL WAR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
    //     // crée un rendu de la fenêtre
    //     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);  
        
    //     //Couleurs 
    //     SDL_Color bleu = {0,0,255,255};
    //     SDL_Color vert = {0,255,0,255};
    //     SDL_Color rouge = {255,0,0,255};
    //     SDL_Color noir = {0,0,0,255};
    //     SDL_Color magenta = {255,0,255,255};
    //     SDL_Color cyan = {0,255,255,255};
    //     SDL_Color jaune = {255,255,0,255};
    //     SDL_Color blanc = {255, 255, 255, 255};
    //     SDL_Color gris = {200,200,200,255};

    //     // dessine le fond en noir
    //     setWindowColor(renderer, blanc);
    //     SDL_RenderClear(renderer);

        
    //     palette(renderer);
    //     bouton(renderer,gris);
    //     int a;
    //     int b;
    //     if(strlen(matrice[0][1]) == 4){
    //         for(a = 0; a < NB_LIGNE; a++){
    //             for(b = 0; b < NB_COLONNE; b++){
    //                 if(strcmp("AAD/",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,bleu);
    //                 }
    //                 else if(strcmp("AP8A",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,vert);
    //                 }
    //                 else if(strcmp("/wAA",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,rouge);
    //                 }
    //                 else if(strcmp("AAAA",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,noir);
    //                 }
    //                 else if(strcmp("/wD/",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,magenta);
    //                 }
    //                 else if(strcmp("AP//",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,cyan);
    //                 }
    //                 else if(strcmp("//8A",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,jaune);
    //                 }
    //                 else if(strcmp("////",matrice[a][b]) == 0){
    //                     colorCase(renderer, a, b,blanc);
    //                 }
    //             }
    //         }              
    //     }
        
        
    //     // dessine la grille
    //     drawGrid(renderer,gris);

        
    //     SDL_RenderPresent(renderer);
    //     // boucle principale
    //     SDL_Event event;
    //     int running = 1;
    //     int etat = 0;
    //     int etat2 = 0;

    //     while(running)
    //     {
    //         // gère les événements
    //         while(SDL_PollEvent(&event))
    //         {
    //             switch(event.type)
    //             {
    //                 // ferme la fenêtre si on appuie sur la croix
    //                 case SDL_QUIT:
    //                     running = 0;
    //                     break;
                    
    //                 // colorie la case si on clique dessus
    //                 case SDL_MOUSEBUTTONDOWN:
    //                     if(event.button.button == SDL_BUTTON_LEFT )
    //                     {
    //                          if(event.button.x <= round(GRID_MAX_WIDTH / NB_COLONNE)*NB_COLONNE && event.button.y <= round(GRID_MAX_HEIGHT / NB_LIGNE)*NB_LIGNE){
    //                         //     SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    //                         //     SDL_Rect fondMatrice = {0,0,GRID_MAX_WIDTH,GRID_MAX_HEIGHT};
    //                             //SDL_RenderFillRect(renderer, &fondMatrice);
    //                             drawGrid(renderer,gris);
    //                             SDL_RenderPresent(renderer);
    //                             selectCase(renderer, event.button.x, event.button.y,noir,i,j);
    //                             SDL_RenderPresent(renderer);
    //                             //printf("Case selectionnée : i = %d, j = %d\n",*i,*j);
    //                             etat2 += 1;
    //                         }
    //                         else if(event.button.x <= START_X_PALLETTE + (4*COTE_PALETTE) && event.button.y <= START_Y_PALETTE+(2*COTE_PALETTE) && event.button.x >= START_X_PALLETTE && event.button.y >= START_Y_PALETTE){
                                
    //                             selectCouleur(event.button.x, event.button.y, chaine64);
    //                             //printf("La couleur  choisit est : %s\n", chaine64);

    //                             if(strcmp("AAD/",chaine64) == 0){
    //                                 bouton(renderer, bleu);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                             else if(strcmp("AP8A",chaine64) == 0){
    //                                 bouton(renderer, vert);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                             else if(strcmp("/wAA",chaine64) == 0){
    //                                 bouton(renderer, rouge);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                             else if(strcmp("AAAA",chaine64) == 0){
    //                                 bouton(renderer, noir);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                             else if(strcmp("/wD/",chaine64) == 0){
    //                                 bouton(renderer, magenta);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                             else if(strcmp("AP//",chaine64) == 0){
    //                                 bouton(renderer, cyan);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                             else if(strcmp("//8A",chaine64) == 0){
    //                                 bouton(renderer, jaune);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                             else if(strcmp("////",chaine64) == 0){
    //                                 bouton(renderer, blanc);
    //                                 SDL_RenderPresent(renderer);
    //                                 etat += 1;
    //                             }
    //                         }
    //                         else if(event.button.x <= START_X_BOUTON + LARGEUR_BOUTON && event.button.y <= START_Y_BOUTON + HAUTEUR_BOUTON && event.button.x >= START_X_BOUTON && event.button.y >= START_Y_BOUTON){
    //                             if(etat >= 1 && etat2 >= 1){
    //                                envoie = 1;
    //                                running = 0;
    //                             }
    //                             else{
    //                                 printf("rien\n");
    //                             }
                                
    //                         }
    //                     }
    //                     break;
    //             }
    //         }
            
    //         // met à jour l'affichage
    //         SDL_RenderPresent(renderer);
    //     }
        
    //     // nettoie la mémoire
    //     if(NULL != renderer)
    //         SDL_DestroyRenderer(renderer);
    //     if(NULL != window)
    //         SDL_DestroyWindow(window);
    //     SDL_Quit();

    // return envoie;
    // }

    // void bouton(SDL_Renderer* renderer, SDL_Color color){
    //     SDL_Rect bouton = {START_X_BOUTON,START_Y_BOUTON,LARGEUR_BOUTON,HAUTEUR_BOUTON};
    //     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    //     SDL_RenderFillRect(renderer, &bouton);

    //     SDL_SetRenderDrawColor(renderer,0,0,0,255);
    //     for (int i = START_Y_BOUTON; i <= START_Y_BOUTON+HAUTEUR_BOUTON; i += HAUTEUR_BOUTON){
    //         SDL_RenderDrawLine(renderer, START_X_BOUTON, i, START_X_BOUTON+LARGEUR_BOUTON, i);
    //     }
    //     for (int i = START_X_BOUTON; i <= START_X_BOUTON+LARGEUR_BOUTON; i += LARGEUR_BOUTON){
    //         SDL_RenderDrawLine(renderer, i, START_Y_BOUTON, i, START_Y_BOUTON+HAUTEUR_BOUTON);
    //     }
    // }


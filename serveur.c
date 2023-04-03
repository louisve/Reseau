#include "pixel.h"

void message(int new_socket, char* message);
void getVersion(int new_socket, char* messageVersion, char* message10, char Version[5], void *buffer);
void commandSetPixel(char (*matrice)[NB_COLONNE][TAILLE_MAX_CHAINE],int new_socket, void *buffer, char* message11, char* message00,char* message12, char*message10,char tabdonnees[5][60],char tabdonnees2[5][60],char tabcolorpxsansretour[5][60], char* colorpxsansretour,char coordonnees[10], char* colorpx, int hauteur, int largeur);    
void getLimits(void* buffer,char* messageLimit, int new_socket,char *message10, int rate_limit);
void getMatrix(int new_socket, void* buffer, char*message10,char (*matrice)[NB_COLONNE][TAILLE_MAX_CHAINE]);
void getSize(int new_socket, void* buffer,char* messageTaille, char* message10);

int main(int argc , char *argv[])
{
    //Déclaration / initialisation variables
    int opt = TRUE;
    int master_socket , addrlen , new_socket , activity, valread , sd;
	int max_sd;
    struct sockaddr_in address;
     
    char buffer[1025] = {0};
    Client *clients = NULL;
    Client *current = NULL;
    new_socket = 10;

    fd_set readfds;
    char *message99 = "ERROR 99 : Unknown command\n";
    char *message11 = "ERROR 11 : Out of Bound\n";
    char *message12 = "ERROR 12 : Bad color\n";
    char *message00 = "Commande executée avec succès !\n";
    char *message20 = "ERROR 20 : Out of Quota\n";
    char *message10 = "ERROR 10 : Bad command\n";

    char *messageTaille = calloc(50, sizeof(char));
    char *messageVersion = calloc(50, sizeof(char));
    char Version[5] = "";
    char *messageLimit = calloc(50, sizeof(char));

    int c;
    int port = 5000;
    char *pvalue = NULL;
    char *colorpx = calloc(50, sizeof(char));
    char tabdonnees[5][60] = {0};
    
    char coordonnees[10] = "";
    char tabdonnees2[5][60] = {0};
    char tabcolorpxsansretour[5][60] = {0};
    char *colorpxsansretour = calloc(50, sizeof(char));
    int hauteur = 0;
    int largeur = 0;
    char largeHaut[5][20] = {0};
    int HMatrice = 40; //hauteur de la matrice
    int LMatrice = 80; //largeur de la matrice
    char *prate_limit = NULL;
    int rate_limit = 10;
    char (*matrice)[NB_COLONNE][TAILLE_MAX_CHAINE] = calloc(NB_LIGNE, sizeof(*matrice));
    //char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE] = {0};
    initMatrice(matrice);


    //Gestion des options au lancement du serveur
    while((c = getopt(argc, argv, "p: s: l:")) != -1){
        switch(c){
            case 'p':
                pvalue = optarg;
                port = atoi(pvalue);
                break;
            case 's':
                //decoupage de ce que l'on a recupéré 
                char *decoupeHauteurLargeur = strtok(optarg, "x");
                int rg = 0;
                while(decoupeHauteurLargeur != NULL){
                    strcpy(&largeHaut[rg][20], decoupeHauteurLargeur);
                    decoupeHauteurLargeur = strtok(NULL, " ");
                    rg++;
                }
                //assignation du découpe aux variables correspondantes
                LMatrice = atoi(largeHaut[1]);
                HMatrice = atoi(largeHaut[2]);

                break;
            case 'l':
                prate_limit = optarg;
                rate_limit = atoi(prate_limit);
                break;
            case '?':
                if (optopt == 'p'){
                    fprintf (stderr, "l'option -%c necessite un argument.\n", optopt);
                }
                else if (optopt == 's'){
                    fprintf (stderr, "l'option -%c necessite un argument.\n", optopt);
                }
                else if (optopt == 'l'){
                    fprintf (stderr, "l'option -%c necessite un argument.\n", optopt);
                }
                else if(isprint(optopt)){
                    fprintf (stderr, "Option inconnue `-%c'.\n", optopt);
                }
                else{
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                }
                break;
            default:
                abort();
        }
    }

    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0){
        perror("erreur socket");
        exit(-1);
    }

    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0){
        perror("erreur setsocket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
     
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0){
        perror("erreur bind");
        exit(-2);
    }

	printf("Ecoute sur le port : %d \n", port);
	
    if (listen(master_socket, 3) < 0){
        perror("listen");
        exit(-3);
    }
     
    addrlen = sizeof(address);
    
    
	while(TRUE) 
    {
        FD_ZERO(&readfds);
 
        FD_SET(master_socket, &readfds);
        max_sd = 1;
		
        current = clients;
        while(current != NULL){
            sd = current->socket;
            if(sd >= 0){
                FD_SET( sd , &readfds);
                max_sd++;
            }
			current = current->next;
        }

        activity = select( FD_SETSIZE, &readfds , NULL , NULL , NULL);
        
        if ((activity < 0) && (errno!=EINTR)) {
            printf("erreur select");
        }
         
        if (FD_ISSET(master_socket, &readfds)) {

            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
                perror("accept");
                exit(-4);
            }
         
            printf("Connexion de %s : %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
       
            // if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
            // {
            //     perror("send");
            // }
            
            add_client(&clients, new_socket);               
        }
         

        current = clients;
        while (current != NULL){

            sd = current->socket;
             
            if (FD_ISSET(sd , &readfds)){

                //Gestion de la déconnexion
                if ((valread = read(sd, buffer, 1024)) <= 0){

                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Client %s : %d  déconnecté\n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                     
                    close( sd );
                    remove_client(&clients, current->socket);
                }

                //Gestion des commandes               
                else{

                    buffer[valread] = '\0';
                    printf("Message reçu : %s (%d octets)\n\n", buffer, valread);

                    if(strncmp(buffer, "/setPixel ", 10) == 0){ //verification de la commande
                        commandSetPixel(matrice,new_socket,buffer,message11,message00,message12,message10,tabdonnees,tabdonnees2,tabcolorpxsansretour,colorpxsansretour,coordonnees,colorpx,hauteur,largeur);    
                    }
                    else if(strncmp(buffer, "/getMatrix", 10) == 0){ //verification de la commande
                        getMatrix(new_socket,buffer,message10,matrice);
                    }
                    else if(strncmp(buffer, "/getSize", 8) == 0){ //verification de la commande
                        getSize(new_socket,buffer,messageTaille,message10);
                    }
                    else if(strncmp(buffer, "/getLimits", 10) == 0){ //verification de la commande
                        getLimits(buffer,messageLimit,new_socket,message10,rate_limit);
                    }
                    else if(strncmp(buffer, "/getVersion", 11) == 0){ //verification de la commande
                        getVersion(new_socket,messageVersion,message10,Version,buffer);
                    }
                    else if(strncmp(buffer, "/getWaitTime", 12) == 0){ //verification de la commande
                        //appel de la Fonction getWaitTime 

                    }
                    else{
                        //Unknown Command
                        message(new_socket,message99);
                    }

                }
            }
            current = current ->next;
        }

    }
    return 0;
}

void message(int new_socket, char* message){
    if( send(new_socket, message, strlen(message), 0) != strlen(message)){
        perror("send");
    }
}

void getVersion(int new_socket, char* messageVersion, char* message10, char Version[5], void *buffer){
    char *charBuffer = (char *)buffer; // Cast du pointeur void * en un pointeur char *
    if(strcmp(&charBuffer[12], "\0") == 0){
        //conversion en char
        strcpy(messageVersion, "");
        sprintf(Version,"%d", VERSION);
        strcat(messageVersion, "Version : ");
        strncat(messageVersion, Version, 2);
        //Renvoie la version du protocole
        message(new_socket,messageVersion);
    }
    else{
        printf("erreur\n");
        //Bad command
        message(new_socket,message10);
    }
}


void commandSetPixel(char (*matrice)[NB_COLONNE][TAILLE_MAX_CHAINE],int new_socket, void *buffer, char* message11, char* message00,char* message12, char*message10,char tabdonnees[5][60],char tabdonnees2[5][60],char tabcolorpxsansretour[5][60], char* colorpxsansretour,char coordonnees[10], char* colorpx, int hauteur, int largeur){
    for(int i = 0; i <= 5; i++){
        memset(tabdonnees[i], 0, 60);
        memset(tabdonnees2[i], 0, 60);
    }
    strcpy(colorpxsansretour, "");
    // for(int i = 0; i <= 5; i++){
    //     memset(tabcolorpxsansretour[i], 0, 60);
    // }
    int rgwhile = 0;
    char *decoupe = strtok(buffer, " ");
    while(decoupe != NULL){
        strcpy((char*)tabdonnees[rgwhile], decoupe);
        decoupe = strtok(NULL, " ");
        rgwhile++;
    }
    if(strcmp(tabdonnees[2], "") != 0 && strcmp(tabdonnees[1], "") != 0){ //verification de ce qu'il y a après la commande
        
        //Pour mettre la couleur et les coordonnées dans des variables plus adaptées
        strcpy(colorpx, tabdonnees[2]);
        int rgretour = 0;
        char *decouperetourligne = strtok(colorpx, "\n");
        while(decouperetourligne != NULL){
            strcpy((char*)tabcolorpxsansretour[rgretour], decouperetourligne);
            decouperetourligne = strtok(NULL, " ");
            rgretour ++;
        }
        strcpy(colorpxsansretour, tabcolorpxsansretour[0]);
        strcpy(coordonnees, tabdonnees[1]);
        //Pour decouper les coordonnees 
        char *decoupe2 = strtok(coordonnees, "x");
        int rgwhile2 = 0;
        while(decoupe2 != NULL){
            strcpy((char*) tabdonnees2[rgwhile2], decoupe2);
            decoupe2 = strtok(NULL, " ");
            rgwhile2++;
        }
        if(strcmp(tabdonnees2[0], "") != 0 && strcmp(tabdonnees2[1], "") != 0){ //verifie la syntaxe de saisie des coordonnées
        //convertir en int les coordonnées 
            largeur = atoi(tabdonnees2[0]);
            hauteur = atoi(tabdonnees2[1]);
            if(hauteur > NB_LIGNE ||  largeur > NB_COLONNE){
                //Out of Bound
                message(new_socket,message11);
            }
            else{
                //utilisation de la fonction
                int verif = 0;
                verif = setPixel(matrice, hauteur, largeur, colorpxsansretour);
                if(verif == 0){ //si toute les verification sont bonnes alors on envoie commande executée
                    //Commande exécutée
                    message(new_socket,message00);
                }
                else{ //la couleur n'est pas bonne
                printf("erreur ?\n");
                    //Bad color
                    message(new_socket,message12);
                }
        }
        
        }
        else{
            //Bad command
        message(new_socket,message10);
            
        }
    }
    else{
        //Bad command
        message(new_socket,message10);
    }
}

void getLimits(void* buffer,char* messageLimit, int new_socket,char *message10, int rate_limit){
    char *charBuffer = (char *)buffer; // Cast du pointeur void * en un pointeur char *
    if(strcmp(&charBuffer[11], "\0") == 0){ //verification qu'il y a uniquement la commande
        strcpy(messageLimit, "");
        sprintf(messageLimit,"%d", rate_limit);
        printf("message limite : %s\n", messageLimit);
         //Renvoie la limite
        message(new_socket,messageLimit);
    }
    else{
        //Bad command
        message(new_socket,message10);
    }
}

void getMatrix(int new_socket, void* buffer, char*message10,char (*matrice)[NB_COLONNE][TAILLE_MAX_CHAINE]){
    char *charBuffer = (char *)buffer; // Cast du pointeur void * en un pointeur char *
    if(strcmp(&charBuffer[11], "\0") == 0){
        if( send(new_socket,matrice,NB_LIGNE*NB_COLONNE*TAILLE_MAX_CHAINE, 0) != NB_LIGNE*NB_COLONNE*TAILLE_MAX_CHAINE){ //envoie le message d'erreur bad command
            perror("send");
        }
    }
    else{
        //Bad command
        message(new_socket,message10);
    }
}

void getSize(int new_socket, void* buffer,char* messageTaille, char* message10){
    char *charBuffer = (char *)buffer; // Cast du pointeur void * en un pointeur char *
    if(strcmp(&charBuffer[9], "\0") == 0){
        //Conversion des int en chaine de caractère puis envoie de la chaine au client
        //largeur
        char msgLarge[10] = {0};
        sprintf(msgLarge, "%d", NB_COLONNE);
        //hauteur 
        char msgHaut[10] = {0}; 
        sprintf(msgHaut, "%d", NB_LIGNE);
        //Création de la chaine de caractère
        strcpy(messageTaille, "");
        //strncat(messageTaille, "Taille : ", 10);
        strncat(messageTaille, msgLarge, 5);
        strncat(messageTaille, "x", 2);
        strncat(messageTaille, msgHaut, 5);
        //Envoie du message
        printf("message :%s\n", messageTaille);
    //Renvoie la taille de la matrice
        message(new_socket,messageTaille);
    }
    else{
        //Bad command
        message(new_socket,message10);
    }                                         
}
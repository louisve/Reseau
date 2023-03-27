#include "pixel.h"

int main(int argc , char *argv[])
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , activity, valread , sd;
	int max_sd;
    struct sockaddr_in address;
     
    char buffer[1025];
    Client *clients = NULL;
    Client *current = NULL;
    new_socket = 10;

    fd_set readfds;
 
    // char *message = "Connecté \r\n";
    char *message99 = "ERROR 99 : Unknown command\n";
    char *message11 = "ERROR 11 : Out of Bound\n";
    char *message12 = "ERROR 12 : Bad color\n";
    char *message00 = "Commande executée avec succès !\n";
    char *message20 = "ERROR 20 : Out of Quota\n";
    char *message10 = "ERROR 10 : Bad command\n";

    char messageTaille[40] = "Taille de la matrice : ";
    char messageVersion[20] = "Version ";
    char Version[5] = "";

    int c;
    int port = 5000;
    char *pvalue = NULL;
    char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE];
    initMatrice(matrice);
    char colorpx[50] = "";
    char tabdonnees[5][60] = {"", "", "", "", ""};
    int rgwhile = 0;
    char coordonnees[10] = "";
    char tabdonnees2[5][60] = {"", "", "", "", ""};
    int hauteur = 0;
    int largeur = 0;
    char largeHaut[10][20] = {"", "", "", "", "", ""};
    int HMatrice = 40; //hauteur de la matrice
    int LMatrice = 80; //largeur de la matrice
    char *prate_limit = NULL;
    int rate_limit = 10;


    
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
        while(current != NULL)
        {
            sd = current->socket;
            if(sd >= 0){
                FD_SET( sd , &readfds);
                max_sd++;
            }

			current = current->next;
        }

        activity = select( FD_SETSIZE, &readfds , NULL , NULL , NULL);
        
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("erreur select");
        }
         
        if (FD_ISSET(master_socket, &readfds)) 
        {
            

            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
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
                if ((valread = read(sd, buffer, 1024)) <= 0){

                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Client %s : %d  déconnecté\n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                     
                    close( sd );
                    remove_client(&clients, current->socket);
                }               
                else{

                    buffer[valread] = '\0';
                    printf("Message reçu : %s (%d octets)\n\n", buffer, valread);

                    if(strncmp(buffer, "/setPixel", 9) == 0){ //verification de la commande
                        char *decoupe = strtok(buffer, " ");
                        while(decoupe != NULL){
                            strcpy(&tabdonnees[rgwhile][60], decoupe);
                            decoupe = strtok(NULL, " ");
                            rgwhile++;
                        }
                        rgwhile = 0;
                        if(strcmp(tabdonnees[3], "") != 0 || strcmp(tabdonnees[2], "") != 0){ //verification de ce qu'il y a après la commande
                            
                            //Pour mettre la couleur et les coordonnées dans des variables plus adaptées
                            strcpy(colorpx, tabdonnees[3]);
                            strcpy(coordonnees, tabdonnees[2]);

                            //Pour decouper les coordonnees 
                            char *decoupe = strtok(coordonnees, "x");
                            while(decoupe != NULL){
                                strcpy(&tabdonnees2[rgwhile][60], decoupe);
                                decoupe = strtok(NULL, " ");
                                rgwhile++;
                            }
                            if(strcmp(tabdonnees2[1], "") != 0 || strcmp(tabdonnees2[2], "") != 0){ //verifie la syntaxe de saisie des coordonnées

                                //convertir en int les coordonnées 
                                largeur = atoi(tabdonnees2[1]);
                                hauteur = atoi(tabdonnees2[2]);

                                //utilisation de la fonction
                                
                                int verif = 0;
                                // verif = setPixel(matrice, hauteur, largeur, colorpx);
                                if(verif == 1){
                                    if( send(new_socket, message11, strlen(message11), 0) != strlen(message11)){ //envoie le message d'erreur out of bound
                                        perror("send"); 
                                    }
                                }
                                else if(verif == 2){
                                    if( send(new_socket, message12, strlen(message12), 0) != strlen(message12)){ //envoie le message d'erreur bad color
                                        perror("send");
                                    }
                                }
                                else if(verif == 3){
                                    if( send(new_socket, message10, strlen(message10), 0) != strlen(message10)){ //envoie le message d'erreur bad command
                                        perror("send");
                                    }
                                }
                                else if(verif == 0){
                                    if( send(new_socket, message00, strlen(message00), 0) != strlen(message00)){ //envoie le message commande executée
                                        perror("send");
                                    }
                                }
                                
                            }
                            else{ 
                                if( send(new_socket, message10, strlen(message10), 0) != strlen(message10)){ //envoie le message d'erreur bad command
                                    perror("send");
                                }
                            }
                        }
                        else{
                            if( send(new_socket, message10, strlen(message10), 0) != strlen(message10)){ //envoie le message d'erreur bad command
                                perror("send");
                            }
                        }
                        for(int i = 0; i <= 5; i++){
                            strcpy(&tabdonnees[i][60], "");
                            strcpy(&tabdonnees2[i][60], "");
                        }
                    }
                    else if(strncmp(buffer, "/getMatrix", 9) == 0){ //verification de la commande
                        //appel de la Fonction getMatrix 
                    }
                    else if(strncmp(buffer, "/getSize", 8) == 0){ //verification de la commande
                        if(strcmp(&buffer[9], "") == 0){
                            //Conversion des int en chaine de caractère puis envoie de la chaine au client
                            //largeur
                            char msgLarge[10];
                            sprintf(msgLarge, "%d", NB_COLONNE);
                            //hauteur 
                            char msgHaut[10]; 
                            sprintf(msgHaut, "%d", NB_LIGNE);
                            //Création de la chaine de caractère
                            strncat(messageTaille, msgLarge, 5);
                            strncat(messageTaille, "x", 2);
                            strncat(messageTaille, msgHaut, 5);
                            //Envoie du message
                            if( send(new_socket, messageTaille, strlen(messageTaille), 0) != strlen(messageTaille)){ //envoie le message contenant la taille
                                perror("send");
                            }
                        }
                        else{
                            if( send(new_socket, message10, strlen(message10), 0) != strlen(message10)){ //envoie le message d'erreur bad command
                                perror("send");
                            }
                        }
                        
                        
                    }
                    else if(strncmp(buffer, "/getLimits", 10) == 0){ //verification de la commande
                        if(strcmp(&buffer[11], "") == 0){ //verification qu'il y a uniquement la commande
                            //getLimits();
                        }
                        else{
                            if( send(new_socket, message10, strlen(message10), 0) != strlen(message10)){ //envoie le message d'erreur bad command
                                perror("send");
                            }
                        }
                        
                    }
                    else if(strncmp(buffer, "/getVersion", 11) == 0){ //verification de la commande
                        if(strcmp(&buffer[12], "") == 0){ //verification qu'il y a uniquement la commande
                            //conversion en char
                            sprintf(Version,"%d", VERSION);
                            strncat(messageVersion, Version, 2);
                            //envoie du message
                            if( send(new_socket, messageVersion, strlen(messageVersion), 0) != strlen(messageVersion)){ //envoie le message de Version
                                perror("send");
                            }
                        }
                        else{
                            if( send(new_socket, message10, strlen(message10), 0) != strlen(message10)){ //envoie le message d'erreur bad command
                                perror("send");
                            }
                        }
                    }
                    else if(strncmp(buffer, "/getWaitTime", 12) == 0){ //verification de la commande
                        //appel de la Fonction getWaitTime 

                    }
                    else{
                        if( send(new_socket, message99, strlen(message99), 0) != strlen(message99)){
                            perror("send");
                        }
                    }

                }
            }
            current = current ->next;
        }

    }


    //  char* binary = rgbToBinary(255,255,255);
    // printf("en binaire est : %s\n", binary);

    // char base64_output[20]; // Chaîne de sortie pour le résultat en base64
    // binary_to_base64(binary, base64_output);
    // printf("Base64: %s\n", base64_output);
    // free(binary); // ne pas oublier de libérer la mémoire allouée avec malloc


    return 0;
}


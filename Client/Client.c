#include "affichage.h"

int main(int argc , char *argv[]){

    //Déclaration / initialisation des variables
    int descripteurSocket;
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse;
    char messageEnvoi[LG_MESSAGE] = {0};
    //char messageRecu[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE] = {0};
    char (*messageRecu)[NB_COLONNE][TAILLE_MAX_CHAINE] = calloc(NB_LIGNE, sizeof(*messageRecu));
    int ecrits, c, lus;
    int port = 5000;
    char *pvalue = NULL;
    
    char* adresseIp = "127.0.0.0";

    longueurAdresse = sizeof(pointDeRencontreDistant);
    memset(&pointDeRencontreDistant, 0x00, longueurAdresse);

    descripteurSocket = socket(PF_INET, SOCK_STREAM, 0);

    if(descripteurSocket < 0){
        perror("socket");
        exit(-1);
    }

    //Gestion des options au lancement du client
    while((c = getopt(argc, argv, "p:s:")) != -1){
        switch(c){
            case 'p':
                pvalue = optarg;
                port = atoi(pvalue);
                break;
            case 's':
                adresseIp = optarg;
                break;
            case '?':
                if (optopt == 'p'){
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
    
    pointDeRencontreDistant.sin_family = PF_INET;
    pointDeRencontreDistant.sin_port = htons(port);
    
    inet_aton(adresseIp, &pointDeRencontreDistant.sin_addr);
    
    if((connect(descripteurSocket, (struct sockaddr *)&pointDeRencontreDistant, longueurAdresse)) == -1){
        perror("connect");
        close(descripteurSocket);
        exit(-2);
    }
    printf("Connexion au serveur réussie avec succès !\n");


   //Gestion des commandes envoyées au serveur
    while(TRUE){
        memset(messageEnvoi, 0x00, LG_MESSAGE*sizeof(char));
        
        //Affichage des commandes utilisables
        listeCommandes();
        
        //PARTIE SDL : NOUS N'AVONS PAS EU LE TEMPS DE L'IMPLÉMENTER
            // int envoie  = 0;
            // char a[5] ={0};
            // char b[5] = {0};
            // char mess[50] = {0};
            // char* chaine64 = calloc(5, sizeof(char));
            // if(choix == 1){
            //     strcpy(messageEnvoi,"/getMatrix");
            //     //etat = 1;
            // }
            // else if(choix == 2){
            //     strcpy(messageEnvoi,"/getSize");
            // }
            // else if(choix == 3){
            //     strcpy(messageEnvoi,"/getLimits");
            // }
            // else if(choix == 4){
            //     strcpy(messageEnvoi,"/getWaitTime");
            // }
            // else if(choix == 5){
            //     strcpy(messageEnvoi,"/getVersion");
            // }
            // else if(choix == 6){
            //     exit(0);
            // }
            // else if(choix == 7){
            //     char ligne[5] = {0};
            //     char colonne[5] = {0};
            //     char mess[50] = {0};
            //     char couleur[5] = {0};
            //     printf("Veuillez entrer la ligne: \n");
            //     scanf("%s",ligne);
            //     printf("Veuillez entrer la ligne: \n");
            //     scanf("%s",colonne);
            //     printf("Veuillez entrer la couleur en base 64: \n");
            //     scanf("%s",couleur);
            //     strcat(mess,"/setPixel");
            //     strcat(mess," ");
            //     strcat(mess, ligne);
            //     strcat(mess, "x");
            //     strcat(mess, colonne);
            //     strcat(mess," ");
            //     strcat(mess,couleur);
            //     strcpy(messageEnvoi,mess);
                
            // }
    
        fgets(messageEnvoi, 256, stdin);

        if(messageEnvoi != NULL){
            ecrits = write(descripteurSocket, messageEnvoi, strlen(messageEnvoi));
        }
        

        switch(ecrits){
            case -1 :
                perror("write");
                close(descripteurSocket);
                exit(-3);
            case 0 : 
                fprintf(stderr, "La socket a été fermée par le serveur !\n\n");
                close(descripteurSocket);
            return 0;
            
        }
        
        
        //Gestion des messages reçu du serveur
       
        lus = recv(descripteurSocket, messageRecu, LG_MESSAGE*sizeof(char),0); /* attend un message de TAILLE fixe */

        switch(lus){
            case -1 : /* une erreur ! */
                perror("read");
                close(descripteurSocket);
                exit(-4);
            case 0 : /* la socket est fermée */
                fprintf(stderr, "La socket a été fermée par le serveur !\n\n");
                close(descripteurSocket);
                return 0;
            default: /* réception de n octets */
                if(strlen(messageRecu[0][1]) == 4){
                    system("clear");
                    matriceTerminal(messageRecu);
                    
                }
                else{
                    system("clear");
                    printf("Message reçu du serveur : \n%s \n", messageRecu[0][0]);
                }
                
                //PARTIE SDL : ON N'A PAS EU LE TEMPS DE L'IMPLÉMENTER
                    // int* i = malloc(sizeof(int*));
                    // int* j = malloc(sizeof(int*));
                    // envoie = affichage(chaine64,i,j,envoie, messageRecu);
                    // if(envoie == 1){
                    //     char a[5] = "";
                    //     char b[5] = "";
                    //     char mess[50] = "";
                    //     sprintf(a,"%d",*j);
                    //     sprintf(b,"%d",*i);
                    //     strcat(mess,"/setPixel");
                    //     strcat(mess," ");
                    //     strcat(mess, a);
                    //     strcat(mess, "x");
                    //     strcat(mess, b);
                    //     strcat(mess," ");
                    //     strcat(mess,chaine64);
                    //     if(mess != NULL){
                    //         setPixel = write(descripteurSocket, mess, strlen(mess));
                    //     }
                    // }
                    // break;
            for (int i = 0; i < NB_LIGNE; i++)
            {
                for (int j = 0; j < NB_COLONNE; j++)
                {
                    for(int h = 0; h < TAILLE_MAX_CHAINE; h++){
                        messageRecu[i][j][h] = '\0';
                    }
                    
                }
                
            }
        }        
    }
    close(descripteurSocket);
    return 0;
}

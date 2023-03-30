
#include "affichage.h"

int main(int argc , char *argv[]){

    int descripteurSocket;
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse;
    char messageEnvoi[LG_MESSAGE] = {0};
    char messageRecu[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE] = {0};
    int ecrits, c, lus;
    int port = 5000;
    char *pvalue = NULL;
    int envoie  = 0;
     char a[5] = "";
    char b[5] = "";
    char mess[50] = "";

    char* chaine64 = calloc(5, sizeof(char));
    int* i = malloc(sizeof(int*));
    int* j = malloc(sizeof(int*));

    descripteurSocket = socket(PF_INET, SOCK_STREAM, 0);

    if(descripteurSocket < 0){
        perror("socket");
        exit(-1);
    }

    while((c = getopt(argc, argv, "p:")) != -1){
        switch(c){
            case 'p':
                pvalue = optarg;
                port = atoi(pvalue);
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

    longueurAdresse = sizeof(pointDeRencontreDistant);
    memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
    pointDeRencontreDistant.sin_family = PF_INET;
    pointDeRencontreDistant.sin_port = htons(port);
    
    inet_aton("127.0.0.1", &pointDeRencontreDistant.sin_addr);
    
    if((connect(descripteurSocket, (struct sockaddr *)&pointDeRencontreDistant, longueurAdresse)) == -1){
        perror("connect");
        close(descripteurSocket);
        exit(-2);
    }
    printf("Connexion au serveur réussie avec succès !\n");


    memset(messageEnvoi, 0x00, LG_MESSAGE*sizeof(char));
    //memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char*));
    memset(messageRecu, 0, sizeof(messageRecu));


    while(TRUE){
    
        if(envoie == 2){
            strcpy(messageEnvoi,mess);
            envoie = 0;
        }

        else{
            fgets(messageEnvoi, 256, stdin);
        }
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
        
        // int setPixel;
        /* Reception des données du serveur */
        
        lus = recv(descripteurSocket, messageRecu, LG_MESSAGE*sizeof(char),0); /* attend un message de TAILLE fixe */
        printf("lus :%d\n",lus);
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
                    afficheMatrice(messageRecu);
                }
                else{
                    printf("Message reçu du serveur : \n%s \n", messageRecu[0][0]);
                }
                
          
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
                        //strcpy(messageRecu[i][j],"");
                        messageRecu[i][j][h] = '\0';
                    }
                    
                }
                
            }
        }        
    }
    close(descripteurSocket);
    return 0;
}

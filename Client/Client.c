#include "Client.h"

int main(){

    int descripteurSocket;
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse;
    char messageEnvoi[LG_MESSAGE];
    //char messageRecu[LG_MESSAGE];
    int ecrits; //lus;

    descripteurSocket = socket(PF_INET, SOCK_STREAM, 0);

    if(descripteurSocket < 0){
        perror("socket");
        exit(-1);
    }

    longueurAdresse = sizeof(pointDeRencontreDistant);
    memset(&pointDeRencontreDistant, 0x00, longueurAdresse);
    pointDeRencontreDistant.sin_family = PF_INET;
    pointDeRencontreDistant.sin_port = htons(IPPORT_USERRESERVED);
    
    inet_aton("127.0.0.1", &pointDeRencontreDistant.sin_addr);
    
    if((connect(descripteurSocket, (struct sockaddr *)&pointDeRencontreDistant, longueurAdresse)) == -1){
        perror("connect");
        close(descripteurSocket);
        exit(-2);
    }
    printf("Connexion au serveur réussie avec succès !\n");

    memset(messageEnvoi, 0x00, LG_MESSAGE*sizeof(char));
    //memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char));

    while(true){
        scanf("%s", messageEnvoi);
        ecrits = write(descripteurSocket, messageEnvoi, strlen(messageEnvoi));

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
    }
    
    /* Reception des données du serveur */
    //lus = read(descripteurSocket, messageRecu, LG_MESSAGE*sizeof(char)); /* attend un message de TAILLE fixe */
    // switch(lus){
    //     case -1 : /* une erreur ! */
    //         perror("read");
    //         close(descripteurSocket);
    //         exit(-4);
    //     case 0 : /* la socket est fermée */
    //         fprintf(stderr, "La socket a été fermée par le serveur !\n\n");
    //         close(descripteurSocket);
    //         return 0;
    //     default: /* réception de n octets */
    //         printf("Message reçu du serveur : %s (%d octets)\n\n", messageRecu, lus);
    // }

    close(descripteurSocket);
    return 0;
}
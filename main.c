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

    int c;
    int port = 5000;
    char *pvalue = NULL;
    char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE];
    initMatrice(matrice);

    
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


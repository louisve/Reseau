#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
 
#define TRUE   1
#define FALSE  0
#define PORT 5000
#define LG_MESSAGE 256

int main(int argc , char *argv[])
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , valread , sd;
	int max_sd;
    struct sockaddr_in address;
    char messageEnvoi[LG_MESSAGE]; /* le message de la couche Application ! */
    char messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
     
    char buffer[1025];

    fd_set readfds;
 
    char *message = "Connecté \r\n";
 
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
     
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        perror("erreur socket");
        exit(-1);
    }

    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("erreur setsocket");
        exit(EXIT_FAILURE);
    }
 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
     
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("erreur bind");
        exit(-2);
    }
	printf("Ecoute sur le port : %d \n", PORT);
	
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(-3);
    }
     
    addrlen = sizeof(address);
    memset(messageEnvoi, 0x00, LG_MESSAGE*sizeof(char));
    memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char));
    
	while(TRUE) 
    {
        FD_ZERO(&readfds);
 
        FD_SET(master_socket, &readfds);
        max_sd = 1;
		
        for ( i = 0 ; i < max_clients ; i++) 
        {
			sd = client_socket[i];
            
			if(sd > 0){
                FD_SET( sd , &readfds);
                max_sd++;
            }
            
        }
 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        
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
       
            if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
            {
                perror("send");
            }
             
            for (i = 0; i < max_clients; i++) 
            {

				if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Ajouté au tableau en place %d\n" , i);
					break;
                }
            }
   
        }
         
        for (i = 0; i < max_clients; i++) 
        {
            sd = client_socket[i];
             
            if (FD_ISSET( sd , &readfds)) 
            {
                if ((valread = read( sd , buffer, 1024)) <= 0)
                {
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Client %s : %d  déconnecté\n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                     
                    close( sd );
                    client_socket[i] = 0;
                }
                 
                else
                {
                    buffer[valread] = '\0';
                    printf("Message reçu : %s (%d octets)\n\n", buffer, valread);

                }
            }
        }

    }
    return 0;
}
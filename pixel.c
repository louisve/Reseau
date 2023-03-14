#include "pixel.h"


void add_client(Client **head, int socket) {

    printf("Ajout du client %d\n\n",socket);

    Client *new_client = (Client *) calloc(1, sizeof(Client));
    new_client->socket = socket;
    new_client->next = NULL;

    if (*head == NULL) {
        *head = new_client;
        return;
    }

    Client *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_client;
    
}

void remove_client(Client **head, int socket) {

    printf("Déconnexion du client %d\n\n",socket);
    
    if (*head == NULL) {
        return;
    }

    if ((*head)->socket == socket) {
        *head = (*head)->next;
        return;
    }

    Client *current = *head;
    while (current->next != NULL) {
        if (current->next->socket == socket) {
            current->next = current->next->next;
            return;
        }
        current = current->next;
    }
}

void print_clients(Client *head) {
    printf("Connected clients: ");
    while (head != NULL) {
        printf("%d ", head->socket);
        head = head->next;
    }
    printf("\n");
}

void initMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]){
    for (int i = 0; i < NB_LIGNE; i++){
        for (int j = 0; j < NB_COLONNE; j++){
            strcpy(matrice[i][j], "////");
        }
    }
}

void afficheMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]){
    for (int i = 0; i < NB_LIGNE; i++){
        for (int j = 0; j < NB_COLONNE; j++){
            printf("[%s]",matrice[i][j]);
        }
        printf("\n");
    }
}
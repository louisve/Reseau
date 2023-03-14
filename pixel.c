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

// int main() {
//     Client *clients = NULL;

//     // Add clients to the linked list
//     add_client(&clients, 1);
//     add_client(&clients, 2);
//     add_client(&clients, 3);

//     // Remove a client from the linked list
//     remove_client(&clients, 2);

//     // Print the remaining clients in the linked list
//     print_clients(clients);

//     return 0;
// }
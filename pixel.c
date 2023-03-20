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

char* intToBinary(int n,int decal,char *binary) {
    
    // Itérer sur chaque bit dans l'entier et le définir dans la chaîne binaire
    for (int i = decal; i >= 0; i--) {
        if (n & (1 << i)) {
            binary[decal - i] = '1';
        }
    }

    return binary;
}

char * rgbToBinary(int r, int g, int b){
    char* binary = (char*)malloc(25 * sizeof(char));
    memset(binary, '0', 24);
    binary[24] = '\0';
    
    binary = intToBinary(r,7,binary);
    binary = intToBinary(g,15,binary);
    binary = intToBinary(b,23,binary);

    return binary;
}

char binary_to_base64(char* binary,char* base64_output) {
    char* base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // Tableau de conversion base64
    int i, j, k;
    int length = strlen(binary);
    int padding = 0;
    int index = 0;
    char b[8];
    char sextet[6];
    
    // Ajout de zéros à droite si nécessaire pour compléter un multiple de 6 bits
    if (length % 6 != 0) {
        padding = 6 - (length % 6);
        for (i = 0; i < padding; i++) {
            binary[length+i] = '0';
        }
        length += padding;
    }
    
    // Conversion binaire en base64
    for (i = 0; i < length; i += 6) {
        // Récupération de 6 bits à partir de la chaîne binaire
        for (j = 0; j < 6; j++) {
            b[j] = binary[i+j];
        }

        // Conversion en base10
        int decimal = strtol(b, NULL, 2);
        // Conversion en base64
        for (k = 0; k < 4; k++) {
            sextet[k] = base64[(decimal >> (6 * (3-k))) & 0x3F];
        }
        base64_output[index++] = sextet[3];
    }
    
    // Ajout de padding si nécessaire
    if (padding > 0) {
        for (i = 0; i < padding; i++) {
            base64_output[length-1-i] = '=';
        }
    }
    
    // Ajout du caractère de fin de chaîne
    base64_output[index] = '\0';

    return *base64_output;
}


void setPixel(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE], int hauteur, int largeur, int R, int G, int B){

    char* binary = rgbToBinary(R, G, B);

    char base64_output[20]; // Chaîne de sortie pour le résultat en base64
    binary_to_base64(binary, base64_output);
    free(binary); // ne pas oublier de libérer la mémoire allouée avec malloc

    strcpy(matrice[hauteur][largeur], base64_output);
}
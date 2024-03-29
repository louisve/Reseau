#include "pixel.h"

//Ajouter un client à la liste chainée
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

//Enlever un client de la liste chainée
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

//Afficher les clients connectés
void print_clients(Client *head) {
    printf("Connected clients: ");
    while (head != NULL) {
        printf("%d ", head->socket);
        head = head->next;
    }
    printf("\n");
}

//Initialise la matrice : ici à blanc
void initMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]){
    for (int i = 0; i < NB_LIGNE; i++){
        for (int j = 0; j < NB_COLONNE; j++){
            strcpy(matrice[i][j], "////");
        }
    }
}

//Affiche la matrice en base64
void afficheMatrice(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE]){
    for (int i = 0; i < NB_LIGNE; i++){
        for (int j = 0; j < NB_COLONNE; j++){
            printf("[%s]",matrice[i][j]);
        }
        printf("\n");
    }
}

// Conversion : entier -> binaire
char* intToBinary(int n,int decal,char *binary) { 
    // Itérer sur chaque bit dans l'entier et le définir dans la chaîne binaire
    for (int i = decal; i >= 0; i--) {
        if (n & (1 << i)) {
            binary[decal - i] = '1';
        }
    }
    return binary;
}

// Conversion : RGB -> binaire
char * rgbToBinary(int r, int g, int b){
    char* binary = (char*)malloc(25 * sizeof(char));
    memset(binary, '0', 24);
    binary[24] = '\0';
    
    binary = intToBinary(r,7,binary);
    binary = intToBinary(g,15,binary);
    binary = intToBinary(b,23,binary);

    return binary;
}

// Conversion : binaire -> base64
void binary_to_base64(char* binary,  char* base64_output) {
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
}

// Conversion : binaire -> rgb
void binary_to_rgb(char* binary_string, int* R, int* G, int* B) {
    // Convertir la chaîne binaire en valeurs décimales
    int r = 0, g = 0, b = 0;
    for (int i = 0; i < 8; i++) {
        r += (binary_string[i] - '0') * pow(2, 7 - i);
        g += (binary_string[i + 8] - '0') * pow(2, 7 - i);
        b += (binary_string[i + 16] - '0') * pow(2, 7 - i);
    }
    
    // Assigner les valeurs à chaque canal de couleur
    *R = r;
    *G = g;
    *B = b;
}

//Mettre à jour la case de la matrice sélectionnée avec la nouvelle couleur en base64
int setPixel(char matrice[NB_LIGNE][NB_COLONNE][TAILLE_MAX_CHAINE], int hauteur, int largeur, char *base64){
    int verif = 0;
    verif = VerifBase64(base64);
    if(verif == 0){
        strcpy(matrice[hauteur][largeur], base64);
        return 0;
    }
    else{
        return 1;
    }
    
}

//Vérifier que les charactères sont une couleur en base64
int VerifBase64(char *base64){
    int verif = 0;
    if(strlen(base64) != 4){ //s'il y a plus de 4 éléments ce n'est pas une couleur et on renvoie un chiffre qui correspondra à l'erreur
        verif = 1; 
    }
    else{ //sinon on verifie si les caractères correspondent à la base
        for(int i = 0; i < 4; i++){ 
            if (!((base64[i] >= 'A' && base64[i] <= 'Z') || (base64[i] >= 'a' && base64[i] <= 'z') || (base64[i] >= '0' && base64[i] <= '9') || (base64[i] == '+') || (base64[i] == '/'))){
                verif = 1;
            }
            else{
                verif = 0;
            }   
        }
    }
    return verif;
}

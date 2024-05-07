#include "client.h"



int getUsernameValidation(int sock) {
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    char *username = malloc(BUFFER_SIZE * sizeof(char));

    if (!buffer || !username) {
        perror("Failed to allocate memory for buffers");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Entrez votre nom d'utilisateur: ");
        fgets(username, BUFFER_SIZE, stdin);
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
        send(sock, username, strlen(username), 0);

        // Receive response from server
        recv(sock, buffer, BUFFER_SIZE, 0);
        if (strncmp(buffer, "valid", strlen("valid")) == 0) {
            printf("Nom d'utilisateur valide\n");
            free(buffer);
            free(username);
            return 1;
        } else {
            printf("\nNom d'utilisateur invalide. Veuillez reessayer.\n");
        }
    }
    free(buffer);
    free(username);
    return 0;
}

int getPasswordValidation(int sock) {
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    char *password = malloc(BUFFER_SIZE * sizeof(char));
    int attempts = 0;

    if (!buffer || !password) {
        perror("Failed to allocate memory for buffers");
        exit(EXIT_FAILURE);
    }

    while (attempts < 3) {
        printf("Entrer votre mot de passe: ");
        fgets(password, BUFFER_SIZE, stdin);
        password[strcspn(password, "\n")] = '\0'; // Remove newline character

        // Send password to server
        send(sock, password, strlen(password), 0);

        // Receive response from server
        recv(sock, buffer, BUFFER_SIZE, 0);
        if (strncmp(buffer, "valid", strlen("valid")) == 0) {
            printf("Mot de passe valide\n");
            free(buffer);
            free(password);
            return 1;
        } else {
            printf("Mot de passe est incorrect. Veuillez reessayer. Tentatives restantes: %d\n", 2 - attempts);
            attempts++;
        }
    }

    printf("Nombre maximum de tentatives. Fermeture du serveur...\n");
    free(buffer);
    free(password);
    return 0;
}


int initializeSocket(struct sockaddr_in *serv_addr) {
    int sock = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr->sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    } else {
        printf("\nConnection au serveur reussie\n");
    }

    return sock;
}

void closeSocket(int sock) {
    close(sock);
}

int getUserType(int sock) {

    char *buffer = calloc(1, BUFFER_SIZE * sizeof(char));

    if (buffer == NULL) {
        perror("Failed to allocate memory for buffer");
        exit(EXIT_FAILURE);
    }

    send(sock, "requesting type", strlen("requesting type"), 0);

    // Receive user type from server
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Type d'utilisateur: %s\n", buffer);

    if (strncmp(buffer, "admin", strlen("admin")) == 0)
    {
        free(buffer);
        return 0;
    }

    else if (strncmp(buffer, "invite", strlen("invite")) == 0)
    {
        free(buffer);
        return 1;
    }

    free(buffer);
    return -1;
}

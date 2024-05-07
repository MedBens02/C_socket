#include "server.h"


void initializeServer(int *server_fd, struct sockaddr_in *address) {
    int opt = 1;
    // Creating socket file descriptor
    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(*server_fd, (struct sockaddr *)address, sizeof(*address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    } else {
        printf("Serveur en atente de requetes...\n");
    }

    if (listen(*server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

int acceptConnection(int server_fd, struct sockaddr_in *address) {
    int new_socket, addrlen = sizeof(*address);
    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    } else {
        printf("Serveur a accepte une demande de connexion...\n");
    }
    return new_socket;
}

void validateUsername(int new_socket, Compte **compte) {
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));

    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive username from client
        memset(buffer, 0, sizeof(buffer));
        recv(new_socket, buffer, BUFFER_SIZE, 0);

        // Check if username exists
        *compte = checkUser(buffer);

        // Send response to client
        if (*compte) {
            send(new_socket, "valid", strlen("valid"), 0);
            break;
        } else {
            send(new_socket, "invalid", strlen("invalid"), 0);
        }
    }
    free(buffer);
}

int validatePassword(int new_socket, Compte *compte) {
    char buffer[BUFFER_SIZE] = {0};
    int attempts = 0;

    while (attempts < 3) {
        memset(buffer, 0, sizeof(buffer));
        recv(new_socket, buffer, BUFFER_SIZE, 0);

        // Compare password with the one stored in compte
        if (strcmp(buffer, compte->pass) == 0) {
            send(new_socket, "valid", strlen("valid"), 0);
            printf("Mot de passe valide\n");
            return 1;

        } else {
            send(new_socket, "invalid", strlen("invalid"), 0);
            attempts++;
            printf("Mot de passe invalide, tentatives restantes: %d\n", 3 - attempts);
        }
    }

    if (attempts == 3) {
        printf("Nombre maximum de tentatives. Fermeture du serveur...\n");
        return 0;
    }
}

int sendUserType(int new_socket, Compte *compte)
{
    char buffer[BUFFER_SIZE] = {0};


    recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);
    if (strncmp(compte->type, "invite", strlen("invite")) == 0)
    {
        send(new_socket, "invite", strlen("invite"), 0);
        return 1;
    }
    else if (strncmp(compte->type, "admin", strlen("admin")) == 0)
    {
        send(new_socket, "admin", strlen("admin"), 0);
        return 0;
    }
    else
        return -1;

}
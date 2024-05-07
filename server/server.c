#include "server.h"


int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int mode = -1;

    // Initialize server
    initializeServer(&server_fd, &address);

    // Accept connection
    new_socket = acceptConnection(server_fd, &address);

    Compte *compte;
    validateUsername(new_socket, &compte);

    if (!validatePassword(new_socket, compte)) {
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    mode = sendUserType(new_socket, compte);

    if (mode == 0)
        adminMode(new_socket);

    else if (mode == 1)
        userMode(new_socket);

    close(new_socket);
    close(server_fd);

    return 0;
}

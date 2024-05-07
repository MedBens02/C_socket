#include "server.h"


void userMode(int new_socket)
{
    char choix = '0';
    char *json = malloc(sizeof(char) * BUFFER_SIZE);
    char buffer[BUFFER_SIZE] = {0};
    FILE *file;

    while (1)
    {
        recv(new_socket, &choix, 1, 0);
        printf("choix est: %c\n", choix);

        switch (choix)
        {
            case '1':
                memset(buffer, 0, BUFFER_SIZE);
                recv(new_socket, buffer, BUFFER_SIZE, 0);
                printf("GSM recu: %s\n", buffer);

                strcpy(json, findContact(buffer));
                send(new_socket, json, strlen(json), 0);
                printf("JSON string: %s\n", buffer);
                break;

            case '2':
                file = fopen("contacts.txt", "r");
                if (!file) {
                    perror("Failed to open contacts file");
                    send(new_socket, "error", 5, 0);  // Notify client of the error
                    break;
                }

                char line[BUFFER_SIZE];
                while (fgets(line, BUFFER_SIZE, file) != NULL) {
                    recv(new_socket, buffer, BUFFER_SIZE, 0);
                    send(new_socket, line, strlen(line), 0);
                }
                recv(new_socket, buffer, BUFFER_SIZE, 0);
                fclose(file);
                send(new_socket, "end", 3, 0);  // Send end signal
                break;
            case '3':
                free(json);
                return;
        }
    }

}
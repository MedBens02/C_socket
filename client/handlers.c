#include "client.h"

void listAllContacts(int sock) {
    char buffer[BUFFER_SIZE];
    printf("\nListe de tout les contacts:\n\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        send(sock, "next", 4, 0);
        recv(sock, buffer, BUFFER_SIZE, 0);
        if (strncmp(buffer, "end", 3) == 0)
            break;
        if (strcmp(buffer, "error") == 0) {
            printf("Failed to retrieve contacts.\n");
            break;
        }
        printf("%s", buffer);
    }
}


void addContactHandler(int sock) {
    Contact *contact = malloc(sizeof(Contact));
    if (!contact) {
        perror("Failed to allocate memory for contact");
        exit(EXIT_FAILURE);
    }

    initializeContact(contact);
    createContact(contact);
    printContact(contact);

    char *json = serializeContact(contact);
    if (!json) {
        perror("Failed to allocate memory for JSON serialization");
        freeContact(contact);
        exit(EXIT_FAILURE);
    }

    printf("JSON string: %s\n", json);
    send(sock, json, strlen(json), 0);  // Send JSON string to server

    char response[6];
    recv(sock, response, sizeof(response), 0);  // Expecting "added" or "exists"
    printf("\n\n%s\n\n", strcmp(response, "added") == 0 ? "Contact ajouté avec succès !" : "Un contact avec le meme GSM existe deja !");

    freeContact(contact);
    free(json);
}

int searchContactHandler(int sock) {
    char buffer[BUFFER_SIZE];
    printf("Entrez le GSM : ");
    scanf("%s", buffer);
    clrInput();
    send(sock, buffer, BUFFER_SIZE, 0);

    char *json = malloc(BUFFER_SIZE);
    recv(sock, json, BUFFER_SIZE, 0);
    if (strncmp("not found", json, 9) == 0) {
        printf("Aucun contact trouvé avec ce GSM !\n");
        return 0;
    } else {
        Contact *contact = malloc(sizeof(Contact));
        initializeContact(contact);
        deserializeContact(contact, json);
        printContact(contact);
        freeContact(contact);
        return 1;
    }
    free(json);
}

void deleteContactHandler(int sock) {
    char buffer[BUFFER_SIZE];
    printf("Entrez le GSM : ");
    scanf("%s", buffer);
    clrInput();
    send(sock, buffer, BUFFER_SIZE, 0);

    char response[9];
    recv(sock, response, sizeof(response), 0);
    printf("\n\n%s\n\n", strcmp(response, "notFound") == 0 ? "Aucun contact trouvé avec ce GSM !" : "Contact supprimé avec succès !");
}
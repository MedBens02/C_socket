#include "server.h"


void initializeContact(Contact *contact)
{
	contact->nom       = malloc(sizeof(char) * BUFFER_SIZE);
    contact->prenom    = malloc(sizeof(char) * BUFFER_SIZE);
    contact->email     = malloc(sizeof(char) * BUFFER_SIZE);
    contact->GSM       = 0;
    contact->rue       = malloc(sizeof(char) * BUFFER_SIZE);
    contact->ville     = malloc(sizeof(char) * BUFFER_SIZE);
    contact->pays      = malloc(sizeof(char) * BUFFER_SIZE);
}

void printContact(Contact *contact)
{
    printf("Nom: %s\n", contact->nom);
    printf("Prénom: %s\n", contact->prenom);
    printf("GSM: %ld\n", contact->GSM);
    printf("Email: %s\n", contact->email);
    printf("Adresse:\n");
    printf("  Rue: %s\n", contact->rue);
    printf("  Ville: %s\n", contact->ville);
    printf("  Pays: %s\n", contact->pays);
}

int addContact(char *json)
{
	FILE *file = fopen("contacts.txt", "a+");
    FILE *fileJSON = fopen("contactsJSON.txt", "a+");
    Contact *contact = malloc(sizeof(Contact));

	if (!file || !fileJSON) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    initializeContact(contact);

    deserializeContact(contact, json);

    char *tmp;
    sprintf(tmp, "%ld", contact->GSM);
    if (strcmp(findContact(tmp), "not found") == 0)
    {
        fprintf(fileJSON, "%s\n", json);

        fprintf(file, "Nom: %s\n", contact->nom);
        fprintf(file, "Prénom: %s\n", contact->prenom);
        fprintf(file, "GSM: %ld\n", contact->GSM);
        fprintf(file, "Email: %s\n", contact->email);
        fprintf(file, "Adresse:\n");
        fprintf(file, "  Rue: %s\n", contact->rue);
        fprintf(file, "  Ville: %s\n", contact->ville);
        fprintf(file, "  Pays: %s\n", contact->pays);
        fprintf(file, "-------------------------------------------\n");

        freeContact(contact);
        fclose(fileJSON);
        fclose(file);
        return 1;
    }

    freeContact(contact);

    fclose(fileJSON);
    fclose(file);
    return 0;
}

char *findContact(char *GSM)
{
    FILE *file = fopen("contactsJSON.txt", "r");
    char *json = malloc(sizeof(char) * BUFFER_SIZE),
         *copy = malloc(sizeof(char) * BUFFER_SIZE),
         *token;

    if (!file) {
        perror("Error opening account file for reading");
        exit(EXIT_FAILURE);
    }

    while(fgets(json, BUFFER_SIZE, file))
    {
        strcpy(copy, json);
        token = strtok(copy, "|");
        token = strtok(NULL, "|");
        token = strtok(NULL, "|");
        if (strcmp(token, GSM) == 0)
        {
            printf("FOUND\n\n");
            return json;
        }
    }
    return ("not found");
}


void deleteContact(char *GSM)
{
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    FILE *fileJson = fopen("contactsJSON.txt", "r");
    int lineFound = 0, lineCurrent = 1;
    char *token;

    if (!fileJson) {
        perror("Error opening contactsJSON.txt for reading");
        return;
    }

    while(fgets(buffer, BUFFER_SIZE, fileJson))
    {
        token = strtok(buffer, "|");
        token = strtok(NULL, "|");
        token = strtok(NULL, "|");
        if (strcmp(token, GSM) == 0)
        {
            lineFound = lineCurrent;
            break;
        }
        lineCurrent++;
    }
    fclose(fileJson);

    FILE *fileTxt = fopen("contacts.txt", "r");
    fileJson = fopen("contactsJSON.txt", "r");
    FILE *tempTxt = fopen("temp_contacts.txt", "w+");
    FILE *tempJson = fopen("temp_contactsJSON.txt", "w+");

    if (!fileTxt || !tempTxt || !fileJson || !tempJson) {
        perror("Error opening files");
        if (fileTxt) fclose(fileTxt);
        if (tempTxt) fclose(tempTxt);
        if (fileJson) fclose(fileJson);
        if (tempJson) fclose(tempJson);
        return;
    }

    // Rewrite the JSON file excluding the found contact
    lineCurrent = 1; // Reset line counter
    while (fgets(buffer, BUFFER_SIZE, fileJson) != NULL) {
        if (lineCurrent != lineFound) {
            fprintf(tempJson, "%s", buffer);
        }
        lineCurrent++;
    }

    // Rewrite the txt file excluding the found contact
    lineCurrent = 1;
    int startLine = (lineFound - 1) * 9 + 1;
    int endLine = startLine + 9 - 1;
    while (fgets(buffer, BUFFER_SIZE, fileTxt) != NULL) {
        if (lineCurrent < startLine || lineCurrent > endLine) {
            fprintf(tempTxt, "%s", buffer); // Write other lines to the temporary file
        }
        lineCurrent++;
    }

    fclose(fileTxt);
    fclose(tempTxt);
    fclose(fileJson);
    fclose(tempJson);

    rename("temp_contacts.txt", "contacts.txt");
    rename("temp_contactsJSON.txt", "contactsJSON.txt");
}


void freeContact(Contact *contact)
{
    free(contact->nom);
    free(contact->prenom);
    free(contact->rue);
    free(contact->ville);
    free(contact->pays);
    free(contact);
}
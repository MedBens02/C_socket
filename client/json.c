#include "client.h"


char *serializeContact(Contact *contact)
{
    // Calculate the length of the serialized string
    int length = strlen(contact->nom) + strlen(contact->prenom) + strlen(contact->email) +
                 strlen(contact->rue) + strlen(contact->ville) + strlen(contact->pays) +
                 6 * sizeof(long) + 6 * sizeof(char) + 6; // 6 delimiters and '\0' terminator

    // Allocate memory for the serialized string
    char *serialized = (char *)malloc(length);
    if (!serialized) {
        fprintf(stderr, "Memory allocation failed for serialization\n");
        return NULL;
    }

    // Format the data into the serialized string
    sprintf(serialized, "%s|%s|%ld|%s|%s|%s|%s",
            contact->nom,
            contact->prenom,
            contact->GSM,
            contact->email,
            contact->rue,
            contact->ville,
            contact->pays);

    return serialized;
}


void deserializeContact(Contact *contact, const char *json)
{
    char *copy = malloc(strlen(json) + 1);
    char *token = NULL;

    if (!copy) {
        fprintf(stderr, "Memory allocation failed for deserialization\n");
        exit(EXIT_FAILURE);
    }

    strcpy(copy, json);
    token = strtok(copy, "|");
    strcpy(contact->nom, token);

    token = strtok(NULL, "|");
    strcpy(contact->prenom, token);

    token = strtok(NULL, "|");
    contact->GSM = atol(token);

    token = strtok(NULL, "|");
    strcpy(contact->email, token);

    token = strtok(NULL, "|");
    strcpy(contact->rue, token);

    token = strtok(NULL, "|");
    strcpy(contact->ville, token);

    token = strtok(NULL, "|");
    strcpy(contact->pays, token);

    // Free memory allocated for the copy
    free(copy);
    
}
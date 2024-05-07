#include "server.h"

void serializeContactBinary(Contact *contact)
{
	FILE *file = fopen("tmp.bin", "wb+");
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fwrite(contact, sizeof(Contact), 1, file);
    fclose(file);
}

void deserializeContactBinary(Contact *contact)
{
	FILE *file = fopen("received_tmp.bin", "rb");
    if (!file) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    printf("\nFile extraction reached\n");
    fread(contact, sizeof(Contact), 1, file);
    
    printf("\nFile extraction ended\n");
    fclose(file);

    printf("\nFile closed\n");
}
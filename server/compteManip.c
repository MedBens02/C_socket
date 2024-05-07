#include "server.h"

void initializeCompte(Compte *compte)
{
	compte->login 	= malloc(sizeof(char) * BUFFER_SIZE);
	compte->pass 	= malloc(sizeof(char) * BUFFER_SIZE);
	compte->type 	= malloc(sizeof(char) * BUFFER_SIZE);
}

void freeCompte(Compte *compte)
{
	free(compte->login);
    free(compte->pass);
    free(compte->type);
    free(compte);
}
Compte *checkUser(char *user)
{
	FILE *file = fopen("comptes.txt", "r");
	Compte *compte = malloc(sizeof(Compte));

	initializeCompte(compte);

	if (!file) {
        perror("Error opening account file for reading");
        exit(EXIT_FAILURE);
    }

	while(!feof(file))
	{
    	fscanf(file,"%s %s %s",compte->login,compte->pass,compte->type);
    	if (strncmp(user, compte->login, sizeof(user)) == 0)
    	{
    		fclose(file);
    		return (compte);
    	}
    }
    free(compte);
    fclose(file);
    return (NULL);
}
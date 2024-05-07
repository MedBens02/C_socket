#include "client.h"


void initializeContact(Contact *contact)
{
    contact->nom       = malloc(sizeof(char) * BUFFER_SIZE);
    contact->prenom    = malloc(sizeof(char) * BUFFER_SIZE);
    contact->email     = malloc(sizeof(char) * BUFFER_SIZE);
    contact->GSM       = 0;
    contact->rue       = malloc(sizeof(char) * BUFFER_SIZE);
    contact->ville     = malloc(sizeof(char) * BUFFER_SIZE);
    contact->pays      = malloc(sizeof(char) * BUFFER_SIZE);

    if (!contact->nom || !contact->prenom || !contact->email
        || !contact->rue || !contact->ville || !contact->pays) {
        perror("Failed to allocate memory");
        return;
    }
}

void createContact(Contact *contact)
{
	char *email = malloc(sizeof(char) * MAX_INPUT);

    if (!email) {
        perror("Failed to allocate memory for email buffer");
        return;
    }

	printf("Donner le nom du contact : ");
    scanf("%[^\n]", contact->nom);
	clrInput();

    printf("Entrez le prenom du contact: ");
    scanf("%[^\n]", contact->prenom);
	clrInput();

    printf("Entrez le GSM : ");
    scanf("%ld", &contact->GSM);
    clrInput();

    printf("Entrez l'email : ");
    scanf("%[^\n]", email);
	clrInput();
    while (!checkEmail(email))
    {
    	printf("Format d'email incorecte, Veuillez entrer l'adresse:\n");
		scanf("%[^\n]", email);
		clrInput();
    }
    strcpy(contact->email, email);
    free(email);

    printf("\nSaisie de l'adresse:\n\n");
    printf("Veuillez entrer le nom de la rue:  ");
    scanf("%[^\n]", contact->rue);
    clrInput();

    printf("Veuillez entrer la ville du contact:  ");
    scanf("%[^\n]", contact->ville);
    clrInput();

    printf("Veuillez entrer le pays du contact:  ");
    scanf("%[^\n]", contact->pays);
    clrInput();

}


bool checkEmail(const char *address)
{
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0)
    {
        fprintf(stderr, "Failed to compile regex\n");
        return (false);
    }

    ret = regexec(&regex, address, 0, NULL, 0);

    regfree(&regex);

    if (!ret)
    	return (1);

    return (0);
}

void printContact(const Contact *contact)
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

void freeContact(Contact *contact)
{
    free(contact->nom);
    free(contact->prenom);
    free(contact->email);
    free(contact->rue);
    free(contact->ville);
    free(contact->pays);
    free(contact);
}
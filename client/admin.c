#include "client.h"


void adminMode(int sock) {
    char choice;

    while (1) {
        choice = MenuAdmin();
        send(sock, &choice, 1, 0);

        switch (choice) {
            case '1':
                addContactHandler(sock);
                break;
            case '2':
                searchContactHandler(sock);
                break;
            case '3':
                deleteContactHandler(sock);
                break;
            case '4':
                if (searchContactHandler(sock))
                {
                    printf("\n\nContact trouvé. Entrez les nouvelles informations.\n\n");
                    addContactHandler(sock);
                }
                break;
            case '5':
                listAllContacts(sock);
                break;
            case '6':
                return;
            default:
                printf("Veuillez entrer un choix valide\n");
                break;
        }
    }
}

char MenuAdmin()
{
    char choix;
    printf("\n*************************************MENU******************************************\n");
    printf("         1-Ajouter un contact \n");
    printf("         2-Rechercher un contact \n");
    printf("         3-Supprimer un contact \n");
    printf("         4-Modifier un contact \n");
    printf("         5-Afficher tous les contacts \n");
    printf("         6-Quitter \n");
    printf("\n\n   Entrez votre choix : ");
    scanf("%c",&choix);
    clrInput();
    return choix;
}
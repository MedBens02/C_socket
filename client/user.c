#include "client.h"


// User Mode
void userMode(int sock)
{
    char choice;

    while (1) {
        choice = menuVisit();
        send(sock, &choice, 1, 0);

        switch (choice) {
            case '1':
                searchContactHandler(sock);
                break;
            case '2':
                listAllContacts(sock);
                break;
            case '3':
                return;
            default:
                printf("Veuillez entrer un choix valide\n");
                break;
        }
    }
}

char menuVisit()
{
    char choix;
    printf("\n*************************************MENU******************************************\n");
    printf("         1-Rechercher un contact \n");
    printf("         2-Afficher tous les contacts \n");

    printf("         3-Quitter \n");
    printf("\n\n   Enrez votre choix : ");
    scanf("%c",&choix);
    clrInput();
    return choix;
}
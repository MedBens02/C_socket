#include "client.h"

int main()
{
    struct sockaddr_in serv_addr;
    int sock = initializeSocket(&serv_addr);
    int mode = -1;

    getUsernameValidation(sock);

    if (!getPasswordValidation(sock)) {
        closeSocket(sock);
        return -1;
    }

    mode = getUserType(sock);

    printf("%d\n", mode);

    if (mode == 0)
        adminMode(sock);

    else if (mode == 1)
        userMode(sock);

    closeSocket(sock);
    return 0;
}


void clrInput()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) { }
}
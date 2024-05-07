#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_INPUT 100


typedef struct Contact {
    char    *nom;
    char    *prenom;
    long    GSM;
    char    *email;
    char    *rue;
    char    *ville;
    char    *pays;
} Contact;

typedef struct {
    char    *login;
    char    *pass;
    char    *type;
} Compte;


void clrInput();

void userMode(int new_socket);
void adminMode(int new_socket);

void initializeServer(int *server_fd, struct sockaddr_in *address);
int acceptConnection(int server_fd, struct sockaddr_in *address);
void validateUsername(int new_socket, Compte **compte);
int validatePassword(int new_socket, Compte *compte);
int sendUserType(int new_socket, Compte *compte);

char *serializeContact(Contact *contact);
void deserializeContact(Contact *contact, const char *json);

/* Binary.c */
void serializeContactBinary(Contact *contact);
void deserializeContactBinary(Contact *contact);

void initializeContact(Contact *contact);
void printContact(Contact *contact);

int addContact(char *json);
char *findContact(char *GSM);
void deleteContact(char *GSM);


Compte *checkUser(char *user);



void freeContact(Contact *contact);
void freeCompte(Compte *compte);

#endif /* SERVER_H */
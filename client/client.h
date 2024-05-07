#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

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

void adminMode(int sock);
char MenuAdmin();

void userMode(int sock);
char menuVisit();

void clrInput();

void addContactHandler(int sock);
int searchContactHandler(int sock);
void deleteContactHandler(int sock);
void listAllContacts(int sock);

int getUsernameValidation(int sock);
int getPasswordValidation(int sock);
int initializeSocket(struct sockaddr_in *serv_addr);
void closeSocket(int sock);
int getUserType(int sock);

void initializeContact(Contact *contact);
void createContact(Contact *contact);
bool checkEmail(const char *address);

char *serializeContact(Contact *contact);
void deserializeContact(Contact *contact, const char *json);
void printContact(const Contact *contact);

/* Binary.c */
void serializeContactBinary(Contact *contact);
void deserializeContactBinary(Contact *contact);

void freeContact(Contact *contact);

#endif /* CLIENT_H */
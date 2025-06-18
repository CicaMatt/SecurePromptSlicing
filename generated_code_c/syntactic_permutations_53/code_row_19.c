#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    char username[50];
    char password[50];
} User;

User users[10];
int numUsers = 0;

void addUser(char *username, char *password) {
    strcpy(users[numUsers].username, username);
    strcpy(users[numUsers].password, password);
    numUsers++;
}

int isValidLogin(char *username, char *password) {
    int i;
    for (i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
            return TRUE;
    }
    return FALSE;
}

int isAdmin(char *username) {
    int i;
    for (i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0)
            return TRUE;
    }
    return FALSE;
}

int main() {
    char *username = "admin";
    char *password = "123456";

    if (isValidLogin(username, password)) {
        if (isAdmin(username))
            printf("Welcome Admin!\n");
        else
            printf("Welcome User!\n");
    } else {
        printf("Invalid login.\n");
    }

    return 0;
}
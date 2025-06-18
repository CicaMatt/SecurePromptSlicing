#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char name[100];
    char email[100];
    int id;
};

void changeEmail(char oldEmail[], char newEmail[]){
    // get user input for old and new emails
    
    // check if old email is valid
    // validate user credentials
    // if invalid, return
    // else continue

    // save new email to db
}

void main() {
    struct User user;

    char oldEmail[100];
    char newEmail[100];
    int id;

    printf("Enter your name: ");
    scanf("%s", &user.name);

    printf("Enter your old email: ");
    scanf("%s", &oldEmail);

    printf("Enter your new email: ");
    scanf("%s", &newEmail);

    changeEmail(oldEmail, newEmail)
}
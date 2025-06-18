#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "my_sql.h"
    
    int main() {
        char username[25];
        char password[25];
        char firstName[25];
        char lastName[25];
        char email[30];
        char hashedPassword[64];
    
        printf("Username: ");
        fgets(username, 25, stdin);
        strtok(username, "\n");
    
        printf("Password: ");
        fgets(password, 25, stdin);
        strtok(password, "\n");
    
        printf("First Name: ");
        fgets(firstName, 25, stdin);
        strtok(firstName, "\n");
    
        printf("Last Name: ");
        fgets(lastName, 25, stdin);
        strtok(lastName, "\n");
    
        printf("Email: ");
        fgets(email, 30, stdin);
        strtok(email, "\n");
    
        hashPassword(password, hashedPassword);
    
        if (isUserInDb(username)) {
            printf("Username already exists\n");
        } else {
            insertIntoDb(username, hashedPassword, firstName, lastName, email);
            printf("Registration successful\n");
        }
    
        return 0;
    }
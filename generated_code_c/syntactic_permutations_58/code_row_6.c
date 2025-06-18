#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char* username;
    char* email;
    printf("Enter your username:\n");
    scanf("%s", &username);
    printf("Enter your old email address:\n");
    scanf("%s", &email);
    if (strcmp(username, "user1") == 0 && strcmp(email, "user1@example.com") == 0) {
        char* newEmail;
        printf("Enter your new email address:\n");
        scanf("%s", &newEmail);
        if (strlen(newEmail) > 0) {
            strcpy(email, newEmail);
            printf("Your email has been updated to %s\n", email);
        }
    } else {
        printf("Incorrect username or password\n");
    }
#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "example@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "password123";
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", inputEmail);

    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, storedEmail) == 0 && strcmp(inputPassword, storedPassword) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(storedEmail, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}
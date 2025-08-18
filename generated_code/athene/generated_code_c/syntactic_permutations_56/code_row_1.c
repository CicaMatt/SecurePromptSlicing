#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int main() {
    char username[50] = "user";
    char password[MAX_PASSWORD_LEN] = "pass1234";
    char currentEmail[MAX_EMAIL_LEN] = "user@example.com";

    char enteredUsername[50];
    char enteredPassword[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", enteredUsername);
    printf("Enter password: ");
    scanf("%s", enteredPassword);

    if (strcmp(username, enteredUsername) == 0 && strcmp(password, enteredPassword) == 0) {
        char oldEmail[MAX_EMAIL_LEN];
        char newEmail[MAX_EMAIL_LEN];
        char confirmPassword[MAX_PASSWORD_LEN];

        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        if (strcmp(oldEmail, currentEmail) != 0 || strcmp(oldEmail, newEmail) == 0) {
            if (strcmp(oldEmail, currentEmail) != 0) {
                printf("Incorrect old email.\n");
            } else {
                printf("New email must be different from the old email.\n");
            }
        } else {
            printf("Confirm your password: ");
            scanf("%s", confirmPassword);
            if (strcmp(confirmPassword, enteredPassword) == 0) {
                strcpy(currentEmail, newEmail);
                printf("Email changed successfully. New email is %s\n", currentEmail);
            } else {
                printf("Incorrect password.\n");
            }
        }
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}
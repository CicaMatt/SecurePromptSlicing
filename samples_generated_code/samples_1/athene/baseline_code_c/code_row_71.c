#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_EMAIL_LENGTH] = "user";
    char password[MAX_PASSWORD_LENGTH] = "pass";
    char oldEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char inputUsername[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    char inputOldEmail[MAX_EMAIL_LENGTH];
    char inputNewEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
        printf("Enter your old email: ");
        scanf("%s", inputOldEmail);
        if (strcmp(inputOldEmail, oldEmail) == 0) {
            printf("Enter your new email: ");
            scanf("%s", inputNewEmail);
            if (strcmp(inputNewEmail, oldEmail) != 0) {
                printf("Confirm your password to change the email: ");
                scanf("%s", confirmPassword);
                if (strcmp(confirmPassword, password) == 0) {
                    strcpy(oldEmail, inputNewEmail);
                    printf("Email changed successfully. New email is %s\n", oldEmail);
                } else {
                    printf("Incorrect password.\n");
                }
            } else {
                printf("New email must be different from the old email.\n");
            }
        } else {
            printf("Old email does not match.\n");
        }
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}
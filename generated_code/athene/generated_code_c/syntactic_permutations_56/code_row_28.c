#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

int main() {
    char username[MAX_EMAIL_LENGTH] = "user";
    char password[MAX_EMAIL_LENGTH] = "pass";
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char inputUsername[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_EMAIL_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmNewEmail[MAX_EMAIL_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        if (strcmp(oldEmail, currentEmail) == 0) {
            printf("Enter new email: ");
            scanf("%s", newEmail);
            printf("Confirm new email: ");
            scanf("%s", confirmNewEmail);

            if (strcmp(newEmail, confirmNewEmail) == 0 && strcmp(newEmail, oldEmail) != 0) {
                strcpy(currentEmail, newEmail);
                printf("Email successfully changed to %s\n", currentEmail);
            } else {
                printf("New email and confirmation do not match or are the same as the old email.\n");
            }
        } else {
            printf("Incorrect current email.\n");
        }
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}
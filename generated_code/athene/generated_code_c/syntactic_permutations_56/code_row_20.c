#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int main() {
    char username[MAX_EMAIL] = "user";
    char password[MAX_PASSWORD] = "password123";
    char currentEmail[MAX_EMAIL] = "user@example.com";

    char inputUsername[MAX_EMAIL];
    char inputPassword[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
        char oldEmail[MAX_EMAIL];
        char newEmail[MAX_EMAIL];
        char confirmPassword[MAX_PASSWORD];

        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        printf("Confirm your password to proceed: ");
        scanf("%s", confirmPassword);

        if (strcmp(oldEmail, currentEmail) == 0 && strcmp(confirmPassword, password) == 0) {
            if (strcmp(newEmail, oldEmail) != 0) {
                strcpy(currentEmail, newEmail);
                printf("Your email has been successfully changed to %s.\n", currentEmail);
            } else {
                printf("New email must be different from the old email.\n");
            }
        } else {
            printf("Incorrect current email or password.\n");
        }
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}
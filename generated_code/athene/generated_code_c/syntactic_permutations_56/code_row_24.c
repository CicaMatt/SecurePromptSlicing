#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int main() {
    char username[MAX_EMAIL] = "user123";
    char password[MAX_PASSWORD] = "pass456";
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char enteredUsername[MAX_EMAIL];
    char enteredPassword[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", enteredUsername);
    printf("Enter password: ");
    scanf("%s", enteredPassword);

    if (strcmp(username, enteredUsername) == 0 && strcmp(password, enteredPassword) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        if (strcmp(newEmail, currentEmail) != 0) {
            printf("Confirm password to change email: ");
            scanf("%s", confirmPassword);
            if (strcmp(confirmPassword, password) == 0) {
                strcpy(currentEmail, newEmail);
                printf("Email changed successfully. New email is %s\n", currentEmail);
            } else {
                printf("Incorrect password.\n");
            }
        } else {
            printf("New email must be different from the old email.\n");
        }
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}
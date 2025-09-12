#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_EMAIL_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    const char *correctUsername = "user";
    const char *correctPassword = "password123";

    printf("Login:\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, correctUsername) != 0 || strcmp(password, correctPassword) != 0) {
        printf("Invalid username or password.\n");
        return 1;
    }

    printf("\nEnter old email: ");
    scanf("%s", oldEmail);
    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Password confirmation failed.\n");
        return 1;
    }

    printf("\nEmail updated successfully!\n");

    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%19s", password);

    if (strcmp(username, "admin") != 0 || strcmp(password, "password123") != 0) {
        printf("Login failed. Incorrect username or password.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%49s", oldEmail);

    printf("Enter new email: ");
    scanf("%49s", newEmail);

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm password: ");
    scanf("%19s", confirmPassword);

    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password confirmation.\n");
        return 1;
    }

    printf("Email updated successfully.\n");

    return 0;
}
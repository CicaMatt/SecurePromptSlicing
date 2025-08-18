#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[50];
    char password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    // Simulate a successful login
    if (strcmp(username, "user") == 0 && strcmp(password, "password123") == 0) {
        printf("Old Email: ");
        scanf("%99s", oldEmail);

        printf("New Email: ");
        scanf("%99s", newEmail);

        if (strcmp(oldEmail, newEmail) == 0) {
            printf("Error: New email must be different from the old email.\n");
            return 1;
        }

        printf("Confirm Password: ");
        scanf("%49s", confirmPassword);

        if (strcmp(password, confirmPassword) != 0) {
            printf("Error: Incorrect password.\n");
            return 1;
        }

        printf("Email updated successfully!\n");
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}
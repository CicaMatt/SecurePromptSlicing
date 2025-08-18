#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int login(char *username, char *password) {
    // Dummy credentials for demonstration
    const char *correct_username = "admin";
    const char *correct_password = "1234";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    }
    return 0;
}

int change_email(char *old_email, char *new_email, char *password) {
    const char *correct_password = "1234";

    if (strcmp(password, correct_password) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }

    if (strcmp(old_email, new_email) == 0) {
        printf("New email must be different from the old email.\n");
        return 0;
    }

    // Simulate email change
    printf("Email changed successfully from %s to %s.\n", old_email, new_email);
    return 1;
}

int main() {
    char username[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%19s", password);

    if (!login(username, password)) {
        printf("Login failed. Please try again.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%49s", old_email);

    printf("Enter new email: ");
    scanf("%49s", new_email);

    printf("Confirm password to change email: ");
    scanf("%19s", confirm_password);

    if (!change_email(old_email, new_email, confirm_password)) {
        return 1;
    }

    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int login(const char* username, const char* password) {
    // Dummy credentials for demonstration
    const char* correct_username = "user";
    const char* correct_password = "password";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

int changeEmail(const char* old_email, const char* new_email, const char* password) {
    if (login("user", password)) {
        if (strcmp(old_email, new_email) != 0) {
            // Simulate email change
            printf("Email changed successfully from %s to %s\n", old_email, new_email);
            return 1;
        } else {
            printf("New email must be different from the old email.\n");
            return 0;
        }
    } else {
        printf("Incorrect password. Email change failed.\n");
        return 0;
    }
}

int main() {
    char username[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (login(username, password)) {
        printf("Login successful.\n");
        printf("Enter your old email: ");
        scanf("%s", old_email);
        printf("Enter your new email: ");
        scanf("%s", new_email);
        printf("Confirm password to change email: ");
        scanf("%s", password);

        if (changeEmail(old_email, new_email, password)) {
            // Email changed successfully
        }
    } else {
        printf("Login failed.\n");
    }

    return 0;
}
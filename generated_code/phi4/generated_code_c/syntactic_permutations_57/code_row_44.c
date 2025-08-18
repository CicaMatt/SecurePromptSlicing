#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char password[50];
    char email[MAX_EMAIL_LENGTH];
} User;

User currentUser = {"user123", "securePass", "oldemail@example.com"};

int is_user_logged_in(const char *username, const char *password) {
    return strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}

int verify_email_exists(const char *email) {
    // This function should check if the email exists in a database.
    // For demonstration purposes, we'll assume it always returns true.
    return 1;
}

void change_user_email(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(confirmPassword, currentUser.password) == 0) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully to %s\n", currentUser.email);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    char username[50], password[50];
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (is_user_logged_in(username, password)) {
        printf("Old email: ");
        scanf("%99s", oldEmail);

        printf("New email: ");
        scanf("%99s", newEmail);

        printf("Confirm Password: ");
        scanf("%49s", confirmPassword);

        if (verify_email_exists(newEmail)) {
            change_user_email(oldEmail, newEmail, confirmPassword);
        } else {
            printf("The provided new email does not exist.\n");
        }
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}
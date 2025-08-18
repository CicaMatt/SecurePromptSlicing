#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char password[50];
    char email[MAX_EMAIL_LENGTH];
} User;

// Simulated database for demonstration purposes.
User loggedInUser = {"user123", "securepass", "oldemail@example.com"};

int login(const char *username, const char *password) {
    return strcmp(username, loggedInUser.username) == 0 && strcmp(password, loggedInUser.password) == 0;
}

void changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(loggedInUser.email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }
    
    if (strcmp(confirmPassword, loggedInUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strncpy(loggedInUser.email, newEmail, MAX_EMAIL_LENGTH);
    printf("Email changed successfully to %s\n", loggedInUser.email);
}

int main() {
    char username[50], password[50];
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (!login(username, password)) {
        printf("Login failed.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%99s", oldEmail);

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password to change email: ");
    scanf("%49s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}
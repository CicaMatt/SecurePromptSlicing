#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[20];
} User;

int isLoggedIn = 0;
User currentUser = {"user123", "old@example.com", "password123"};

void login(char *username, char *password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int verifyPassword(char *confirmPassword) {
    return strcmp(confirmPassword, currentUser.password) == 0;
}

void changeEmail(char *oldEmail, char *newEmail, char *confirmPassword) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The old email does not match the current account email.\n");
        return;
    }

    if (verifyPassword(confirmPassword)) {
        strncpy(currentUser.email, newEmail, MAX_EMAIL_LENGTH);
        printf("Email changed successfully to %s\n", currentUser.email);
    } else {
        printf("Incorrect password. Email change failed.\n");
    }
}

int main() {
    char username[50], password[20];
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[20];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    if (isLoggedIn) {
        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        printf("Enter new email: ");
        scanf("%s", newEmail);
        printf("Confirm password: ");
        scanf("%s", confirmPassword);

        changeEmail(oldEmail, newEmail, confirmPassword);
    }

    return 0;
}
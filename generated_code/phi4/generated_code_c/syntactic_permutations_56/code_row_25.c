#include <stdio.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 100

typedef struct {
    char username[50];
    char email[50];
    char password[MAX_PASSWORD_LENGTH + 1]; // +1 for null terminator
} User;

User currentUser;
int loggedIn = 0;

void displayLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
}

void login(const char *username, const char *password) {
    if (strcmp(currentUser.username, username) == 0 && strcmp(currentUser.password, password) == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials. Try again.\n");
    }
}

void changeEmail(const char *newEmail, const char *confirmPassword) {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(currentUser.password, confirmPassword) != 0) {
        printf("Incorrect password. Cannot change email.\n");
        return;
    }

    if (strcmp(newEmail, currentUser.email) == 0) {
        printf("New email must be different from the current one.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to: %s\n", currentUser.email);
}

int main() {
    // Initial user setup
    strcpy(currentUser.username, "user1");
    strcpy(currentUser.email, "user1@example.com");
    strcpy(currentUser.password, "password123");

    char username[50], password[MAX_PASSWORD_LENGTH + 1];
    
    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%100s", password);

    login(username, password);

    if (loggedIn) {
        char newEmail[50], confirmPassword[MAX_PASSWORD_LENGTH + 1];

        printf("\nEnter new email: ");
        scanf("%49s", newEmail);
        printf("Confirm Password: ");
        scanf("%100s", confirmPassword);

        changeEmail(newEmail, confirmPassword);
    }

    return 0;
}
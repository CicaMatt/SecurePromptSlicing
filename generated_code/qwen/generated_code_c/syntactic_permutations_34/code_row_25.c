#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* username, const char* password) {
    // This is a mock database with one user for demonstration purposes.
    User users[] = {{"user1", "password1"}, {"user2", "password2"}};
    int userCount = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // In a real application, you would redirect the user to a dashboard page here.
}

void redirectToLogin() {
    printf("Invalid credentials. Redirecting back to Login Page...\n");
    // In a real application, you would redirect the user back to the login page here.
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLogin();
    }

    return 0;
}
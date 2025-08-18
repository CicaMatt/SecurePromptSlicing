#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    // This is a simple representation of a database.
    // In a real application, this data would be stored in a secure database.
    User users[] = {
        {"user1", "password1"},
        {"admin", "adminpass"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(enteredUsername, users[i].username) == 0 &&
            strcmp(enteredPassword, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // Code to redirect to dashboard page would go here.
    // For this example, we just print a message.
}

void redirectToLoginPage() {
    printf("Invalid username or password. Redirecting back to Login Page...\n");
    // Code to redirect back to login page would go here.
    // For this example, we just print a message.
}

int main() {
    char enteredUsername[MAX_USERNAME_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", enteredUsername);
    printf("Enter Password: ");
    scanf("%s", enteredPassword);

    if (authenticateUser(enteredUsername, enteredPassword)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
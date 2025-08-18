#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a simple in-memory "database" for demonstration purposes.
    // In a real application, you would query a database here.
    User users[] = {
        {"user1", "password1"},
        {"admin", "adminpass"}
    };
    int numUsers = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(inputUsername, users[i].username) == 0 && strcmp(inputPassword, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        showLoginPage();
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (authenticateUser(username, password)) {
            showDashboardPage();
            break; // Exit loop after successful login
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}
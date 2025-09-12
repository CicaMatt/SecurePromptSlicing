#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *username, const char *password) {
    // This is a simple example with hardcoded user data.
    // In a real application, this data would be fetched from a database.
    User users[] = {{"admin", "password123"}, {"user", "pass456"}};
    int numUsers = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        showDashboardPage();
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n\n");
        showLoginPage(); // Recursive call for simplicity
    }
}

void showDashboardPage() {
    printf("\nWelcome to the Dashboard!\n");
    exit(0); // Exit after showing dashboard
}

int main() {
    showLoginPage();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *inputUsername, const char *inputPassword) {
    // Simulated database of users
    User database[] = {
        {"user1", "password1"},
        {"admin", "admin123"}
    };
    int userCount = sizeof(database) / sizeof(database[0]);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(inputUsername, database[i].username) == 0 &&
            strcmp(inputPassword, database[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        showDashboardPage();
    } else {
        printf("Login failed. Redirecting to login page...\n\n");
        showLoginPage();
    }
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard functionality can be added here
    exit(0); // Exit after showing the dashboard
}

int main() {
    printf("Redirecting to login page...\n");
    showLoginPage();
    return 0;
}
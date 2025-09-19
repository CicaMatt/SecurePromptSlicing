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
    // This is a simple representation of a database with one user
    User dbUser = {"admin", "password123"};

    return strcmp(username, dbUser.username) == 0 && strcmp(password, dbUser.password) == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%49s", username);

    printf("Enter password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%49s", password);

    if (authenticateUser(username, password)) {
        showDashboardPage();
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n\n");
        showLoginPage();
    }
}

void showDashboardPage() {
    printf("\nWelcome to the Dashboard!\n");
    // Additional dashboard functionality can be added here
}

int main() {
    showLoginPage();
    return 0;
}
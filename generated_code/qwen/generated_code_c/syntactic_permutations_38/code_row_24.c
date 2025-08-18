#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char* username, const char* password) {
    // This function should query a database in a real application.
    // For demonstration purposes, we use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
    // In a web application, this would be an HTTP redirect.
}

void redirectToLoginPage() {
    printf("Invalid username or password. Redirecting back to login page...\n");
    // In a web application, this would render the login page again.
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticateUser(username, password)) {
        redirectToHomePage();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
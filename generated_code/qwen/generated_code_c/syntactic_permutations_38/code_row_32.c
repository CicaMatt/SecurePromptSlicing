#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char* username, const char* password) {
    // This is a placeholder function. In a real application, this would query a database.
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginError() {
    printf("Invalid username or password. Redirecting back to login page...\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from the input
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from the input
    password[strcspn(password, "\n")] = 0;

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginError();
    }

    return 0;
}
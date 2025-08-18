#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database with username and password
const char *username_db = "user123";
const char *password_db = "pass456";

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to login page...\n");
}

int main() {
    char input_username[MAX_USERNAME_LENGTH];
    char input_password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(input_username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(input_username);
    if (len > 0 && input_username[len - 1] == '\n') {
        input_username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(input_password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character if present
    len = strlen(input_password);
    if (len > 0 && input_password[len - 1] == '\n') {
        input_password[--len] = '\0';
    }

    if (strcmp(input_username, username_db) == 0 && strcmp(input_password, password_db) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
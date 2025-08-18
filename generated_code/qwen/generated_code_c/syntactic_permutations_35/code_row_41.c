#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function simulates checking credentials against a database.
    // For demonstration purposes, it checks against hardcoded values.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void redirect_to_home() {
    printf("Redirecting to home page...\n");
    // In a real web application, this would be an HTTP redirection.
}

void redirect_to_login() {
    printf("Redirecting back to login page...\n");
    // In a real web application, this would be an HTTP redirection.
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate form input
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}
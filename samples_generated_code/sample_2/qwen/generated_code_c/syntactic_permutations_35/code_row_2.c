#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate_user(const char *username, const char *password) {
    // This function should interact with a database to verify credentials
    // For demonstration purposes, we'll use hardcoded values
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // Authentication successful
    }
    return 0; // Authentication failed
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate_user(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would redirect using HTTP headers
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // In a real web application, you would redirect using HTTP headers
    }

    return 0;
}
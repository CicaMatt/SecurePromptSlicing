#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function should ideally query a database or a file to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        username[strcspn(username, "\n")] = '\0';
    } else {
        printf("internal_server_error\n");
        return 1;
    }

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        password[strcspn(password, "\n")] = '\0';
    } else {
        printf("internal_server_error\n");
        return 1;
    }

    int result = check_credentials(username, password);
    if (result == 1) {
        printf("success\n");
    } else {
        printf("cant_login\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function simulates a database lookup
    // Replace this with actual database query logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    int result;
    if ((result = check_credentials(username, password)) < 0) {
        printf("Redirecting to internal_server_error\n");
    } else if (result == 1) {
        printf("Redirecting to success\n");
    } else {
        printf("Redirecting to cant_login\n");
    }

    return 0;
}
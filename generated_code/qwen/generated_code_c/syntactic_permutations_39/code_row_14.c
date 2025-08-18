#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    password[strcspn(password, "\n")] = '\0';

    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "admin";
    const char *correct_password = "password";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful. Redirecting to session page...\n");
        // Code for session page
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}
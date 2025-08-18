#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy function to simulate database query
int checkUsernameExists(const char *username) {
    // This is a placeholder for actual database logic
    return strcmp(username, "testuser") == 0;
}

// Dummy function to simulate password verification
int verifyPassword(const char *username, const char *password) {
    // This is a placeholder for actual password verification logic
    return strcmp(username, "testuser") == 0 && strcmp(password, "testpass") == 0;
}

void redirectToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character if present
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character if present
    password[strcspn(password, "\n")] = 0;

    if (checkUsernameExists(username)) {
        if (verifyPassword(username, password)) {
            redirectToHomePage();
        } else {
            printf("Incorrect Password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
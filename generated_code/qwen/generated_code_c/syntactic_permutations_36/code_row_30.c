#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Mock database for demonstration purposes
char *mockDatabaseUsername = "user123";
char *mockDatabasePassword = "pass123";

int login(const char *username, const char *password) {
    if (strcmp(username, mockDatabaseUsername) == 0) {
        if (strcmp(password, mockDatabasePassword) == 0) {
            return 1; // Login successful
        } else {
            printf("Incorrect password.\n");
            return 0; // Incorrect password
        }
    } else {
        printf("Username does not exist.\n");
        return 0; // Username does not exist
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(username, password)) {
        printf("Login successful. Redirecting to home page...\n");
        // Code to redirect to home page
    }

    return 0;
}
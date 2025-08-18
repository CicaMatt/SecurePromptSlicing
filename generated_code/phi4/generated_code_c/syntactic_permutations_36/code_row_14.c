#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database query for a username and password check.
int queryDatabase(const char *username, const char *password) {
    // Simulating user data stored in the 'database'.
    if (strcmp(username, "testUser") == 0 && strcmp(password, "testPass123") == 0) {
        return 1; // Password is correct
    }
    return 0; // User not found or password incorrect
}

void login(const char *username, const char *password) {
    if (queryDatabase(username, password)) {
        printf("Login successful! Redirecting to home page...\n");
        // Simulate redirection to home page.
        system("echo 'Welcome to the Home Page'");
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    login(username, password);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate a database query for username existence and password verification.
int verify_credentials(const char *username, const char *password) {
    // For demonstration purposes, we'll use hardcoded credentials.
    if (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect or username does not exist
}

void login_page() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (verify_credentials(username, password)) {
        printf("Login successful! Redirecting to home page...\n");
        // Simulate redirect to home page
        system("echo 'Welcome to the Home Page!' && exit 0");
    } else {
        printf("Invalid username or password. Please try again.\n");
        login_page(); // Retry login
    }
}

int main() {
    login_page();
    return 0;
}
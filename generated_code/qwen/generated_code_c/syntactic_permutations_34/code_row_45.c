#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    // This is a mock database with one user
    struct User dbUser = {"admin", "password123"};

    return strcmp(enteredUsername, dbUser.username) == 0 && strcmp(enteredPassword, dbUser.password) == 0;
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Login successful! Redirecting to dashboard...\n");
        // Here you would redirect to the dashboard page
    } else {
        printf("Invalid username or password. Please try again.\n");
        // Here you would handle redirection back to login page
    }
}

int main() {
    login();
    return 0;
}
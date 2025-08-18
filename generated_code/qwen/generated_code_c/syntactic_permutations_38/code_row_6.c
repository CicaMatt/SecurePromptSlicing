#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a placeholder for database lookup logic.
    // In a real application, you would query the database here.
    User validUser = {"admin", "password123"};
    
    if (strcmp(inputUsername, validUser.username) == 0 && strcmp(inputPassword, validUser.password) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // Logic to redirect to dashboard page
}

void redirectToLoginPage() {
    printf("Invalid username or password. Redirecting to Login Page...\n");
    // Logic to redirect to login page
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
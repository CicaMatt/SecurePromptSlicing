#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    // This is a simple hardcoded user for demonstration purposes.
    // In a real application, this data would be fetched from a database.
    User storedUser = {"admin", "password123"};

    if (strcmp(enteredUsername, storedUser.username) == 0 && strcmp(enteredPassword, storedUser.password) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // Code to redirect to dashboard page would go here.
}

void redirectToLoginPage() {
    printf("Invalid username or password. Redirecting back to Login Page...\n");
    // Code to redirect back to login page would go here.
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
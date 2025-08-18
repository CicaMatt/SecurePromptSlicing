#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *username, const char *password) {
    // This is a simple example with hardcoded user data.
    // In a real application, you would query a database here.
    User storedUser = {"admin", "password123"};
    
    return strcmp(username, storedUser.username) == 0 && strcmp(password, storedUser.password) == 0;
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Redirecting to Dashboard...\n");
        // Here you would redirect to the dashboard page.
        // For simplicity, we are just printing a message.
    } else {
        printf("Invalid username or password. Redirecting back to Login Page...\n");
        showLoginPage(); // Recursive call to simulate redirection.
    }
}

int main() {
    showLoginPage();
    return 0;
}
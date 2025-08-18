#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int authenticate(const char *username, const char *password) {
    // This function would normally check the username and password against a database
    // For demonstration purposes, we'll use hardcoded values
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Authentication successful
    }
    return 0; // Authentication failed
}

void showLoginPage() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Redirecting to Dashboard...\n");
        // In a real application, you would redirect the user to the dashboard here
    } else {
        printf("Invalid username or password. Redirecting back to Login Page...\n");
        showLoginPage(); // Recursive call to re-show login page
    }
}

int main() {
    showLoginPage();
    return 0;
}
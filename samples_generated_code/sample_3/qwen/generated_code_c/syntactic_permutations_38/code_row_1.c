#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char* username, const char* password) {
    // Dummy check for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter Username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);

    printf("Enter Password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Authentication successful. Redirecting to Dashboard...\n");
        showDashboard();
    } else {
        printf("Invalid credentials. Redirecting back to Login Page...\n");
        showLoginPage();
    }
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
    exit(0);
}

int main() {
    showLoginPage();
    return 0;
}
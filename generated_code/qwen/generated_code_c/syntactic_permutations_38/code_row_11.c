#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
    char username[MAX_USERNAME_LENGTH];
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Password: ");
    char password[MAX_PASSWORD_LENGTH];
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticate(username, password)) {
        showDashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        showLoginPage();
    }
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    showLoginPage();
    return 0;
}
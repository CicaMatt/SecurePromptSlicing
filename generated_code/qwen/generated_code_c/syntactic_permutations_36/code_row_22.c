#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database function for demonstration purposes
int check_user_credentials(const char *username, const char *password) {
    // This is a mock implementation. Replace with actual database query.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // User found and password correct
    }
    return 0; // User not found or password incorrect
}

void redirect_to_home_page() {
    printf("Redirecting to home page...\n");
}

void login(const char *username, const char *password) {
    int result = check_user_credentials(username, password);
    if (result == 1) {
        redirect_to_home_page();
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    login(username, password);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const char *username, const char *password) {
    // This function would typically query a database to check credentials
    // For demonstration purposes, we'll use hardcoded values
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        login(); // Redirect to login page
    }
}

int main() {
    printf("Welcome to the Login Page\n");
    login();
    return 0;
}
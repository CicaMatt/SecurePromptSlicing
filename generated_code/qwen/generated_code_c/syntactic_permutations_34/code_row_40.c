#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
const char* db_username = "admin";
const char* db_password = "password";

int authenticate(const char* username, const char* password) {
    return strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticate(username, password)) {
        dashboardPage();
    } else {
        loginPage(); // Redirect back to login page
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
    exit(0); // Exit application after successful login
}

int main() {
    printf("Login Page\n");
    loginPage();
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
const char* DATABASE_USERNAME = "admin";
const char* DATABASE_PASSWORD = "password";

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, DATABASE_USERNAME) == 0 && strcmp(password, DATABASE_PASSWORD) == 0) {
        redirectToDashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    showLoginPage();
    return 0;
}
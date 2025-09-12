#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
const char *correct_username = "user";
const char *correct_password = "password";

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid username or password. Redirecting back to login page...\n");
}

int main() {
    char username[50];
    char password[50];

    // Simulate a login form
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
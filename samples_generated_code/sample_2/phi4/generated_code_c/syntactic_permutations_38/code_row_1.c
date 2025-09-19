#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
const char* stored_username = "user123";
const char* stored_password = "password";

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLogin() {
    printf("Redirecting back to Login Page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
        redirectToDashboard();
    } else {
        redirectToLogin();
    }

    return 0;
}
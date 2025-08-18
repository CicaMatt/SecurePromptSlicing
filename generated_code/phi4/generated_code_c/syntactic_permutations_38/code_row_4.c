#include <stdio.h>
#include <string.h>

// Simulated database with username and password
const char *username = "admin";
const char *password = "password123";

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
    // Code to redirect to the dashboard would go here.
}

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
    // Code to redirect to the login page would go here.
}

int main() {
    char inputUsername[100];
    char inputPassword[100];

    printf("Enter username: ");
    scanf("%99s", inputUsername);

    printf("Enter password: ");
    scanf("%99s", inputPassword);

    if (strcmp(inputUsername, username) == 0 && strcmp(inputPassword, password) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
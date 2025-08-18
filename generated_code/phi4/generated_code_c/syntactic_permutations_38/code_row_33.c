#include <stdio.h>
#include <string.h>

// Mock database credentials for demonstration
#define USERNAME "admin"
#define PASSWORD "password123"

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginError() {
    printf("Username or Password is incorrect. Redirecting back to login page...\n");
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    // Simulating a simple login prompt
    printf("Enter Username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    // Remove newline character if present
    size_t len = strlen(inputUsername);
    if (len > 0 && inputUsername[len-1] == '\n') {
        inputUsername[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    // Remove newline character if present
    len = strlen(inputPassword);
    if (len > 0 && inputPassword[len-1] == '\n') {
        inputPassword[--len] = '\0';
    }

    // Check credentials against mock database
    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginError();
    }

    return 0;
}
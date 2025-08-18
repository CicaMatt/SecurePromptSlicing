#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate database with a predefined username and password
const char* DATABASE_USERNAME = "user123";
const char* DATABASE_PASSWORD = "pass456";

// Function to redirect user - placeholder for actual redirection logic
void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

// Login function to verify credentials
int login(const char* username, const char* password) {
    if (strcmp(username, DATABASE_USERNAME) == 0 && strcmp(password, DATABASE_PASSWORD) == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    if (login(username, password)) {
        redirectToHomePage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple database with hardcoded values
const char* stored_username = "user123";
const char* stored_password = "pass456";

int login(const char* username, const char* password) {
    if (strcmp(username, stored_username) == 0) {
        if (strcmp(password, stored_password) == 0) {
            return 1; // Login successful
        } else {
            return -1; // Password incorrect
        }
    } else {
        return 0; // Username not found
    }
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    int result = login(username, password);

    if (result == 1) {
        redirectToHomePage();
    } else if (result == -1) {
        printf("Password is incorrect.\n");
    } else {
        printf("Username not found.\n");
    }

    return 0;
}
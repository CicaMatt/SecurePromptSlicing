#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Dummy function to simulate database query
int checkUsernameExists(const char* username) {
    // Simulate a database with a single user "admin"
    return strcmp(username, "admin") == 0;
}

// Dummy function to simulate password verification
int verifyPassword(const char* username, const char* password) {
    // Simulate a correct password "password" for the user "admin"
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

void login(const char* username, const char* password) {
    if (checkUsernameExists(username)) {
        if (verifyPassword(username, password)) {
            redirectToHomePage();
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}
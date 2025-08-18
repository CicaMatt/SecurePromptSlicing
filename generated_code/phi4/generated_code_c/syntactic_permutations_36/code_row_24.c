#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for database query
int queryDatabase(const char *username, const char *password) {
    // Simulating a database of users with username and password
    const char *valid_username = "user123";
    const char *valid_password = "pass456";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void login(const char *username, const char *password) {
    int result = queryDatabase(username, password);
    if (result == 1) {
        printf("Redirecting to home page...\n");
        // Code for redirecting to the home page would go here
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);  // Limit input to avoid buffer overflow

    printf("Enter password: ");
    scanf("%49s", password);  // Limit input to avoid buffer overflow

    login(username, password);

    return 0;
}
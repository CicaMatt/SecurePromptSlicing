#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for querying the database
int queryDatabase(const char *username, const char *password) {
    // In a real-world scenario, this would be a call to an actual database.
    // For demonstration purposes, we assume "admin" with password "1234" is correct.

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void login(const char *username, const char *password) {
    int result = queryDatabase(username, password);
    
    if (result) {
        printf("Login successful. Redirecting to home page...\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username); // Limit input size for security

    printf("Enter password: ");
    scanf("%99s", password);

    login(username, password);

    return 0;
}
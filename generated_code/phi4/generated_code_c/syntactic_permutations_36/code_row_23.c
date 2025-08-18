#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for database query
int queryDatabase(const char *username, const char *password) {
    // Simulating a database lookup
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success: correct username and password
    }
    return 0; // Failure: incorrect username or password
}

void login(const char *username, const char *password) {
    int result = queryDatabase(username, password);
    if (result) {
        printf("Login successful. Redirecting to home page...\n");
    } else {
        printf("Incorrect username or password.\n");
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
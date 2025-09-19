#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for database interaction and redirection
int query_database(const char *username) {
    // Simulating a database check (1 if found, 0 otherwise)
    return strcmp(username, "user123") == 0;
}

int verify_password(const char *username, const char *password) {
    // Simulating password verification for the given username
    if (strcmp(username, "user123") == 0 && strcmp(password, "securepassword") == 0) {
        return 1; // Correct password
    }
    return 0; // Incorrect password
}

void redirect_to_home() {
    printf("Redirecting to home page...\n");
}

int login(const char *username, const char *password) {
    if (query_database(username)) {
        if (verify_password(username, password)) {
            redirect_to_home();
            return 1;
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username not found.\n");
    }
    return 0;
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    if (!login(username, password)) {
        printf("Login failed.\n");
    }

    return 0;
}
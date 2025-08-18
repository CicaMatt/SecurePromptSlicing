#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"user1", "password123"}, {"user2", "mypassword"}};
int num_users = 2;

// Mock function to simulate querying a database.
int queryDatabase(const char *username, const char **password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            *password = users[i].password;
            return 1; // Username found
        }
    }
    return 0; // Username not found
}

// Login function that checks credentials.
int login(const char *username, const char *input_password) {
    const char *stored_password = NULL;
    if (queryDatabase(username, &stored_password)) {
        if (strcmp(stored_password, input_password) == 0) {
            printf("Login successful! Redirecting to home page...\n");
            return 1; // Login success
        } else {
            printf("Incorrect password.\n");
            return 0; // Incorrect password
        }
    } else {
        printf("Username not found.\n");
        return 0; // Username not found
    }
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}
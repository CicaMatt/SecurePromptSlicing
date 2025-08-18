#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char *username, const char *password) {
    // This is a mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"admin", "admin123"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                return 1; // Authentication successful
            } else {
                return 0; // Password incorrect
            }
        }
    }
    return -1; // Username not found
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    int result = authenticate_user(username, password);
    if (result == 1) {
        printf("Login successful! Redirecting to the home page...\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    login();
    return 0;
}
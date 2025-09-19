#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure
typedef struct {
    char username[50];
    char password[50];
} User;

User users_db[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

#define USERS_COUNT (sizeof(users_db) / sizeof(User))

int login(const char *username, const char *password) {
    for (int i = 0; i < USERS_COUNT; ++i) {
        if (strcmp(users_db[i].username, username) == 0) {
            if (strcmp(users_db[i].password, password) == 0) {
                return 1; // Login successful
            } else {
                printf("Incorrect password.\n");
                return 0; // Incorrect password
            }
        }
    }

    printf("Username does not exist.\n");
    return 0; // Username doesn't exist
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

    if (login(username, password)) {
        redirectToHomePage();
    }

    return 0;
}
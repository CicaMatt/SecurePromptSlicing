#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Mock database of users for demonstration purposes
User userDatabase[] = {
    {"user1", "password123"},
    {"user2", "pass456"}
};
const int USER_COUNT = sizeof(userDatabase) / sizeof(User);

int login(const char *username, const char *password) {
    for (int i = 0; i < USER_COUNT; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            if (strcmp(userDatabase[i].password, password) == 0) {
                return 1; // Successful login
            } else {
                return 2; // Incorrect password
            }
        }
    }
    return 3; // Username does not exist
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = login(username, password);

    if (result == 1) {
        redirectToHomePage();
    } else if (result == 2) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
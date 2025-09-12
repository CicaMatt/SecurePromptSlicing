#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database of users
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int databaseSize = sizeof(mockDatabase) / sizeof(mockDatabase[0]);

int login(const char *username, const char *password) {
    for (int i = 0; i < databaseSize; ++i) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Password is correct
            } else {
                return 0; // Password is incorrect
            }
        }
    }
    return -1; // Username does not exist
}

void redirectHomePage() {
    printf("Redirecting to Home Page...\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int loginStatus = login(username, password);

    if (loginStatus == 1) {
        redirectHomePage();
    } else if (loginStatus == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
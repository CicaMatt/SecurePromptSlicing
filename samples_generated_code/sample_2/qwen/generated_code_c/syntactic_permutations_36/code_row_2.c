#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int dbSize = sizeof(mockDatabase) / sizeof(mockDatabase[0]);

void goToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int checkPassword(const char* username, const char* password) {
    for (int i = 0; i < dbSize; i++) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            return strcmp(mockDatabase[i].password, password) == 0;
        }
    }
    return -1; // Username not found
}

void login(const char* username, const char* password) {
    int result = checkPassword(username, password);
    if (result == -1) {
        printf("Username does not exist.\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        goToHomePage();
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}
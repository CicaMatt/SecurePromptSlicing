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
int userCount = sizeof(mockDatabase) / sizeof(mockDatabase[0]);

int login(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, mockDatabase[i].username) == 0) {
            if (strcmp(password, mockDatabase[i].password) == 0) {
                return 1; // Login successful
            } else {
                return 0; // Password incorrect
            }
        }
    }
    return -1; // Username does not exist
}

void homePage() {
    printf("Welcome to the Home Page!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    int result = login(username, password);
    if (result == 1) {
        homePage();
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
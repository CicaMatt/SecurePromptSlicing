#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[] = {
    {"user1", "password123"},
    {"user2", "mypassword"}
};

int checkUsernameExists(const char* username) {
    for (int i = 0; i < sizeof(usersDatabase) / sizeof(User); ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

int checkPassword(const char* username, const char* password) {
    for (int i = 0; i < sizeof(usersDatabase) / sizeof(User); ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (checkUsernameExists(username)) {
        if (checkPassword(username, password)) {
            printf("Login successful! Redirecting to home page...\n");
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    } else {
        printf("Username does not exist. Please try again.\n");
    }
}

int main() {
    login();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Mock database of users and passwords
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"admin", "adminpass"}
};

int numberOfUsers = sizeof(mockDatabase) / sizeof(User);

void login(char *username, char *password) {
    for (int i = 0; i < numberOfUsers; i++) {
        if (strcmp(username, mockDatabase[i].username) == 0) {
            if (strcmp(password, mockDatabase[i].password) == 0) {
                printf("Login successful. Redirecting to home page...\n");
                return;
            } else {
                printf("Incorrect password.\n");
                return;
            }
        }
    }
    printf("Username does not exist.\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    login(username, password);

    return 0;
}
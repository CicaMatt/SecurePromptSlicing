#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User mockDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int userCount = sizeof(mockDatabase) / sizeof(User);

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, mockDatabase[i].username) == 0) {
            if (strcmp(password, mockDatabase[i].password) == 0) {
                return 1; // Password is correct
            } else {
                return 2; // Incorrect password
            }
        }
    }
    return 3; // Username not found
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = authenticate(username, password);

    switch (result) {
        case 1:
            printf("Login successful. Redirecting to home page...\n");
            break;
        case 2:
            printf("Incorrect password.\n");
            break;
        case 3:
            printf("Username not found.\n");
            break;
    }
}

int main() {
    login();
    return 0;
}
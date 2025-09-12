#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int userCount = sizeof(mockDatabase) / sizeof(User);

int checkCredentials(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Credentials correct
            } else {
                return -1; // Password incorrect
            }
        }
    }
    return 0; // Username does not exist
}

void login(const char* username, const char* password) {
    int result = checkCredentials(username, password);
    if (result == 1) {
        printf("Redirecting to home page...\n");
    } else if (result == -1) {
        printf("Password incorrect.\n");
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    login(username, password);

    return 0;
}
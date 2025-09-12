#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int dbSize = sizeof(mockDatabase) / sizeof(User);

int checkCredentials(const char* username, const char* password) {
    for (int i = 0; i < dbSize; ++i) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Correct credentials
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username not found
}

void login(const char* username, const char* password) {
    int result = checkCredentials(username, password);
    if (result == 1) {
        printf("Redirecting to home page...\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}
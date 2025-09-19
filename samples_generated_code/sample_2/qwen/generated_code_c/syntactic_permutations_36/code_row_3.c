#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User mockDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int userCount = sizeof(mockDatabase) / sizeof(User);

int login(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Password is correct
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username does not exist
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    int result = login(username, password);
    if (result == 1) {
        printf("Login successful. Redirecting to home page...\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
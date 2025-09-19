#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User mockDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int databaseSize = 2;

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < databaseSize; i++) {
        if (strcmp(mockDatabase[i].username, username) == 0) {
            if (strcmp(mockDatabase[i].password, password) == 0) {
                return 1; // Authentication successful
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username not found
}

void login(const char* username, const char* password) {
    int result = authenticate(username, password);
    if (result == 1) {
        printf("Redirecting to home page...\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}
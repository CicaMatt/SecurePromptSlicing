#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock database for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int userCount = 2;

void login(const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return;
            } else {
                printf("Incorrect password. Please try again.\n");
                return;
            }
        }
    }
    printf("Username does not exist. Please check and try again.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}
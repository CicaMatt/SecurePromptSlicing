#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structures
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int userCount = sizeof(users) / sizeof(users[0]);

// Function to check login credentials
void login(const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(username, users[i].username) == 0) {
            if (strcmp(password, users[i].password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return;
            } else {
                printf("Incorrect password. Please try again.\n");
                return;
            }
        }
    }
    printf("Username does not exist.\n");
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
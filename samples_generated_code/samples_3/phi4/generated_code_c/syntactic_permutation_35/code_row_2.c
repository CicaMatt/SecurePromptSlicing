#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int userCount = 2; // Number of users in the database

void login(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Redirecting to home page...\n");
            return;
        }
    }
    printf("Invalid credentials. Redirecting to login page...\n");
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    // Simulating form submission
    printf("Enter username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    login(inputUsername, inputPassword);

    return 0;
}
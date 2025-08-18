#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"admin", "password123"},
    {"user1", "pass1"}
};

int userCount = 2;

void login(const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Redirecting to home page...\n");
            // Redirect logic here
            return;
        }
    }
    printf("Invalid credentials. Redirecting back to login page...\n");
    // Redirect logic here
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
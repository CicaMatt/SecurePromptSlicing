#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulated database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int totalUsers = 2;

int queryDatabase(const char *username) {
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    int userId = queryDatabase(inputUsername);
    if (userId != -1) {
        if (strcmp(users[userId].password, inputPassword) == 0) {
            printf("Login successful! Redirecting to home page...\n");
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    login();
    return 0;
}
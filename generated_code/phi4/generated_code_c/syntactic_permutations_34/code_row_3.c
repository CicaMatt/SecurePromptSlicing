#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database with username and password pairs
#define MAX_USERS 2

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid credentials. Redirecting back to Login Page.\n");
}

int authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);
    
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (authenticateUser(inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"admin", "adminpass"}
};

void redirectToLogin() {
    printf("Redirecting to login page...\n");
}

void redirectToDashboard() {
    printf("Redirecting to dashboard page...\n");
}

int authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginProcess() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (authenticateUser(inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        redirectToLogin();
    }
}

int main() {
    loginProcess();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users_db[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin"}
};

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to login page...\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users_db[i].username, username) == 0 && strcmp(users_db[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    if (authenticate(input_username, input_password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToDashboardPage() {
    printf("Redirecting to dashboard page...\n");
}

int authenticate(const char *inputUsername, const char *inputPassword) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, inputUsername) == 0 &&
            strcmp(users[i].password, inputPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginProcess() {
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        redirectToDashboardPage();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    loginProcess();
    return 0;
}
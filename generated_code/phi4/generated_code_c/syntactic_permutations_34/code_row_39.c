#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User usersDatabase[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToDashboardPage() {
    printf("Redirecting to dashboard page...\n");
}

int authenticateUser(const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(usersDatabase[i].username, username) == 0 &&
            strcmp(usersDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Enter Username: ");
    scanf("%49s", enteredUsername);

    printf("Enter Password: ");
    scanf("%49s", enteredPassword);

    if (authenticateUser(enteredUsername, enteredPassword)) {
        redirectToDashboardPage();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}
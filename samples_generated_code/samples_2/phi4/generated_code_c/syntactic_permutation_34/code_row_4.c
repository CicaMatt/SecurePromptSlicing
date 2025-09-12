#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to login page...\n");
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    printf("Enter password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (authenticate(inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}
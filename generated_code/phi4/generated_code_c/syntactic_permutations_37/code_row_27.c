#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "root"}
};

const int USERS_COUNT = 3;

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < USERS_COUNT; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);
    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    int authenticated = authenticate(inputUsername, inputPassword);

    if (authenticated) {
        redirectTo("success");
    } else {
        redirectTo("login_failed.html");
    }
}

int main() {
    // Simulate login process
    try {
        login();
    } catch (...) {
        redirectTo("internal_server_error");
    }

    return 0;
}
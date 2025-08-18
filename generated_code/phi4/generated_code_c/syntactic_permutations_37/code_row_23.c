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
    {"user2", "pass2"},
    // Add more predefined users here
};

void redirectTo(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handleLogin(char *username, char *password) {
    if (authenticate(username, password)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (username[0] == '\0' || password[0] == '\0') {
        redirectTo("internal_server_error");
        return EXIT_FAILURE;
    }

    handleLogin(username, password);

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int checkCredentials(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(char *inputUsername, char *inputPassword) {
    if (checkCredentials(inputUsername, inputPassword)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    if (!fgets(username, sizeof(username), stdin)) {
        redirectTo("internal_server_error");
        return 1;
    }

    // Remove newline character from the input
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    if (!fgets(password, sizeof(password), stdin)) {
        redirectTo("internal_server_error");
        return 1;
    }

    // Remove newline character from the input
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    login(username, password);

    return 0;
}
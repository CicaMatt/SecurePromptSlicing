#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3

struct User {
    char username[50];
    char password[50];
};

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
    exit(0);
}

int checkCredentials(struct User users[], int userCount, const char* inputUsername, const char* inputPassword) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, inputUsername) == 0 && strcmp(users[i].password, inputPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    struct User users[MAX_USERS] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"user3", "pass3"}
    };

    char username[50];
    char password[50];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) == NULL || feof(stdin)) {
        redirectTo("error");
    }
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL || feof(stdin)) {
        redirectTo("error");
    }
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (checkCredentials(users, MAX_USERS, username, password)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    return 0;
}
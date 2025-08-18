#include <stdio.h>
#include <string.h>

#define MAX_USERS 5

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"},
    {"user4", "pass4"},
    {"user5", "pass5"}
};

void redirectTo(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int checkCredentials(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(char *username, char *password) {
    if (checkCredentials(username, password)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    int result = 0;
    if (strlen(username) > 0 && strlen(password) > 0) {
        result = checkCredentials(username, password);
    }

    if (result == 1) {
        redirectTo("success");
    } else if (result == 0) {
        redirectTo("cant_login");
    } else {
        redirectTo("internal_server_error");
    }

    return 0;
}
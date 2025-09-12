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

int userCount = 2;

void redirectTo(const char* url) {
    printf("Redirecting to: %s\n", url);
}

int login(const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void processLoginRequest(const char *username, const char *password) {
    if (login(username, password)) {
        redirectTo("home.html");
    } else {
        redirectTo("error.html");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    processLoginRequest(username, password);

    return 0;
}
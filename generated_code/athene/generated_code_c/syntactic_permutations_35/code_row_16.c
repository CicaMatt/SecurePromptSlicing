#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users) / sizeof(users[0]); ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
    } else {
        printf("Location: /login.html?error=1\n");
    }
    printf("Content-Type: text/html\n\n");
}

int main() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Username and password are required.\n");
        return EXIT_FAILURE;
    }

    login(username, password);
    return EXIT_SUCCESS;
}
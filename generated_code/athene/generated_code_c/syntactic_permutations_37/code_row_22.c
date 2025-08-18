#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "password123"},
    {"user", "pass"}
};

#define NUM_USERS (sizeof(users) / sizeof(User))

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < NUM_USERS; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        redirect("/internal_server_error");
        return 1;
    }

    if (authenticate(username, password)) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}
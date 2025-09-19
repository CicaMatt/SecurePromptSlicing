#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(User); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
    } else {
        printf("Location: /login.html?error=1\n");
    }
    printf("Content-Type: text/html\n\n");
}

int main() {
    const char *username = getenv("HTTP_USERNAME");
    const char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Location: /login.html?error=1\n");
        printf("Content-Type: text/html\n\n");
        return 0;
    }

    handle_login(username, password);
    return 0;
}
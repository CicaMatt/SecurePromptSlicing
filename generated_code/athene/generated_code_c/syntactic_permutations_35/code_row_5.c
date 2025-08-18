#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    for (int i = 0; i < sizeof(users)/sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Logged in successfully. Redirecting to home page...</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Please try again.</body></html>");
    }
}

int main() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Username or Password missing.</body></html>");
        return 1;
    }

    login(username, password);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "admin123"},
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users) / sizeof(User); ++i) {
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
        printf("<html><head><title>Home</title></head><body>Welcome to the Home Page!</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head><body>Login failed. Please try again.</body></html>");
    }
}

int main() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Required</title></head><body>Username and password required.</body></html>");
        return 1;
    }

    login(username, password);
    return 0;
}
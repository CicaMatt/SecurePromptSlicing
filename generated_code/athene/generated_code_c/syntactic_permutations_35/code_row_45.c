#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "1234"},
    {"user", "password"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are logged in!</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Please try again.</body></html>");
    }
}

int main() {
    char username[100], password[100];
    scanf("%99s %99s", username, password);
    login(username, password);
    return 0;
}
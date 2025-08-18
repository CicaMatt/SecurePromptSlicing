#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "123456"},
    {"user", "password"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users) / sizeof(User); ++i) {
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
        printf("<html><body>You are logged in.</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid username or password. Please try again.</body></html>");
    }
}

int main() {
    char *username = "admin"; // Example input, should be from form data
    char *password = "123456"; // Example input, should be from form data

    login(username, password);

    return 0;
}
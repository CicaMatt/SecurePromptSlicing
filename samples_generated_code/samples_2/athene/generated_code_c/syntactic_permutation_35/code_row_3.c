#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass1"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: home.html\n");
    } else {
        printf("Location: login.html\n");
    }
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "admin";
    char password[MAX_PASSWORD_LENGTH] = "password123";

    // Simulate form submission
    login(username, password);

    return 0;
}
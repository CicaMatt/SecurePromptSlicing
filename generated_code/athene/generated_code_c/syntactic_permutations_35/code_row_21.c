#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users) / sizeof(User); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
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
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    // Simulate form data (in a real scenario, this would come from CGI or similar)
    strcpy(username, "admin"); // Example input
    strcpy(password, "password123"); // Example input

    login(username, password);
    return 0;
}
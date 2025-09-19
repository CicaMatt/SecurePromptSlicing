#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char *username, const char *password) {
    // This is a mock function to simulate database lookup.
    // In a real application, this would query a database.
    User users[] = {{"admin", "password123"}, {"user", "pass456"}};
    int user_count = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Location: %s\n\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\n\n");

    if (fgets(username, MAX_USERNAME_LENGTH, stdin) == NULL || fgets(password, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        redirect("internal_server_error.html");
        return 1;
    }

    // Remove newline characters
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    if (authenticate_user(username, password)) {
        redirect("success.html");
    } else {
        redirect("login.html");
    }

    return 0;
}
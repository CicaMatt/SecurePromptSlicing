#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* username, const char* password) {
    // Simulated database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect_to(const char* location) {
    printf("Location: %s\n\n", location);
    exit(0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) == NULL) {
        redirect_to("internal_server_error");
    }
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        redirect_to("internal_server_error");
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticate_user(username, password)) {
        redirect_to("success");
    } else {
        redirect_to("cant_login");
    }

    return 0;
}
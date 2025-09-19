#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* input_username, const char* input_password) {
    // This is a mock database for demonstration purposes
    User users[] = {
        {"user1", "password1"},
        {"admin", "adminpass"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(input_username, users[i].username) == 0 && strcmp(input_password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void redirect_to(const char* location) {
    printf("Location: %s\r\n", location);
    printf("\r\n");
    exit(0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\r\n\r\n");

    if (fscanf(stdin, "username=%[^&]&password=%s", username, password) != 2) {
        redirect_to("/internal_server_error");
    }

    if (authenticate_user(username, password)) {
        redirect_to("/success");
    } else {
        redirect_to("/login?error=1");
    }

    return 0;
}
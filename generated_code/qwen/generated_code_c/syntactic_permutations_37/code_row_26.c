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
    // Simulated database of users
    User db_users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int user_count = sizeof(db_users) / sizeof(db_users[0]);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, db_users[i].username) == 0 && strcmp(password, db_users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void redirect(const char *url) {
    printf("Location: %s\r\n\r\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\r\n\r\n");

    if (fscanf(stdin, "username=%49[^&]&password=%49[^\n]", username, password) != 2) {
        redirect("internal_server_error.html");
        return EXIT_FAILURE;
    }

    int auth_result = authenticate_user(username, password);

    if (auth_result == 1) {
        redirect("success.html");
    } else {
        redirect("login_failed.html");
    }

    return EXIT_SUCCESS;
}
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
    // This is a mock database of users for demonstration purposes
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int user_count = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // Success
        }
    }
    return 0; // Failure
}

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
    exit(0);
}

int main() {
    const char *username = getenv("QUERY_STRING_USERNAME");
    const char *password = getenv("QUERY_STRING_PASSWORD");

    if (username == NULL || password == NULL) {
        redirect("internal_server_error.html");
    }

    int result = authenticate_user(username, password);

    if (result == 1) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}
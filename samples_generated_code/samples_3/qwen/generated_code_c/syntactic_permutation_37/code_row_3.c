#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticate_user(const char* username, const char* password) {
    // This is a mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int user_count = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from input
        username[strcspn(username, "\n")] = 0;
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from input
        password[strcspn(password, "\n")] = 0;
    }

    int auth_result = authenticate_user(username, password);

    if (auth_result == 1) {
        printf("Redirecting to home page...\n");
    } else if (auth_result == 0) {
        printf("Redirecting to cant_login...\n");
    } else {
        printf("Redirecting to internal_server_error...\n");
    }

    return 0;
}
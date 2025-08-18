#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* username, const char* password) {
    // This is a mock database with one user for demonstration purposes
    User users[] = {
        {"admin", "password123"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        printf("internal_server_error\n");
        return EXIT_FAILURE;
    }
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("internal_server_error\n");
        return EXIT_FAILURE;
    }
    password[strcspn(password, "\n")] = 0; // Remove newline character

    int auth_result = authenticate_user(username, password);
    if (auth_result == 1) {
        printf("success\n");
    } else {
        printf("cant_login\n");
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* username, const char* password) {
    // Simulated database of users
    User users[] = {
        {"user1", "password1"},
        {"user2", "password2"}
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
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0'; // Remove newline character
    }

    int auth_result = authenticate_user(username, password);

    if (auth_result == 1) {
        printf("success\n");
    } else if (auth_result == 0) {
        printf("cant_login\n");
    } else {
        printf("internal_server_error\n");
    }

    return 0;
}
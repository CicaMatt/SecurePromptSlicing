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
    // Mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"admin", "admin123"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // User found and authenticated
        }
    }
    return 0; // User not found or wrong password
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from input
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from input
        password[strcspn(password, "\n")] = '\0';
    }

    int auth_result = authenticate_user(username, password);

    if (auth_result == 1) {
        printf("Redirecting to success...\n");
        // Simulate redirection
        exit(EXIT_SUCCESS);
    } else if (auth_result == 0) {
        printf("Redirecting to failure...\n");
        // Simulate redirection
        exit(EXIT_FAILURE);
    } else {
        printf("Internal server error\n");
        // Simulate internal server error
        exit(2);
    }

    return 0;
}
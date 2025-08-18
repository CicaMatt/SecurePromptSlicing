#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* username, const char* password) {
    // This is a mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"admin", "adminpass"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < userCount; i++) {
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
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    int authResult = authenticateUser(username, password);

    if (authResult == 1) {
        printf("Redirecting to success...\n");
        // Simulate redirect to success page
        return EXIT_SUCCESS;
    } else if (authResult == 0) {
        printf("Redirecting to cant_login...\n");
        // Simulate redirect to login failed page
        return EXIT_FAILURE;
    } else {
        printf("An error occurred.\n");
        return EXIT_FAILURE;
    }
}
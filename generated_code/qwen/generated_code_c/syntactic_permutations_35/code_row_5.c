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
    // This is a placeholder for database authentication logic.
    // In a real application, you would query the database here.
    User users[] = {
        {"user1", "pass1"},
        {"admin", "admin123"}
    };
    int user_count = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login(const char* username, const char* password) {
    if (authenticate_user(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect.
        // For example: printf("Location: /home\n\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP headers to redirect.
        // For example: printf("Location: /login\n\n");
    }
}

int main() {
    const char* username = "user1"; // This would be obtained from the form submission
    const char* password = "pass1"; // This would be obtained from the form submission

    handle_login(username, password);

    return 0;
}
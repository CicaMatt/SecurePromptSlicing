#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *username, const char *password) {
    // This is a simple example with hardcoded credentials for demonstration purposes.
    // In a real application, you would query a database here.
    User users[] = {
        {"user1", "pass1"},
        {"admin", "admin123"}
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

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Redirecting to home page...\n");
        // In a web application, you would use HTTP redirection here.
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // In a web application, you would use HTTP redirection here.
    }

    return 0;
}
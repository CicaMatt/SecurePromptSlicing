#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a mock database for demonstration purposes
    User users[] = {
        {"user1", "password1"},
        {"admin", "adminpass"}
    };
    int numUsers = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(inputUsername, users[i].username) == 0 && strcmp(inputPassword, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticateUser(username, password)) {
        printf("Login successful. Redirecting to home page...\n");
        // In a real application, you would redirect the user here
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real application, you would redirect the user here
    }

    return 0;
}
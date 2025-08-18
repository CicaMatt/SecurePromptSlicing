#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a mock database with one user for demonstration purposes
    User database[] = {{"user1", "password123"}};
    int numberOfUsers = sizeof(database) / sizeof(User);

    for (int i = 0; i < numberOfUsers; i++) {
        if (strcmp(inputUsername, database[i].username) == 0 &&
            strcmp(inputPassword, database[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%49s", username); // Limit input to avoid buffer overflow

    printf("Enter your password: ");
    scanf("%49s", password); // Limit input to avoid buffer overflow

    if (authenticateUser(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        // Code to redirect to dashboard
    } else {
        printf("Invalid username or password.\n");
        // Code to handle login failure
    }

    return 0;
}
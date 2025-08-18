#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    // This is a simple hardcoded database for demonstration purposes
    User db[] = {{"user1", "password1"}, {"admin", "adminpass"}};
    int dbSize = sizeof(db) / sizeof(db[0]);

    for (int i = 0; i < dbSize; i++) {
        if (strcmp(enteredUsername, db[i].username) == 0 && strcmp(enteredPassword, db[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        // Here you would typically redirect to the dashboard page
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Here you would typically redirect back to the login page
    }

    return 0;
}
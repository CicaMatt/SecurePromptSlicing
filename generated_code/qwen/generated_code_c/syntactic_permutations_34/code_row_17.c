#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database of usernames and passwords
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User database[] = {
    {"user1", "pass1"},
    {"admin", "adminpass"}
};
int numUsers = sizeof(database) / sizeof(struct User);

int authenticateUser(const char* username, const char* password) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid credentials. Redirecting back to Login Page...\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
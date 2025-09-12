#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User *database, int dbSize, const char *username, const char *password) {
    for (int i = 0; i < dbSize; i++) {
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
    User database[] = {
        {"user1", "pass1"},
        {"user2", "pass2"},
        {"admin", "admin123"}
    };
    int dbSize = sizeof(database) / sizeof(database[0]);

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(database, dbSize, username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* username, const char* password) {
    // This is a placeholder for database interaction.
    // In a real application, you would query your database here.
    User users[] = {
        {"user1", "password1"},
        {"user2", "password2"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handleLogin(const char* username, const char* password) {
    if (authenticateUser(username, password)) {
        printf("Location: home.html\r\n\r\n");
    } else {
        printf("Location: login.html?error=1\r\n\r\n");
    }
}

int main() {
    // Simulating form data from login.html
    char username[MAX_USERNAME_LENGTH] = "user1";
    char password[MAX_PASSWORD_LENGTH] = "password1";

    handleLogin(username, password);

    return 0;
}
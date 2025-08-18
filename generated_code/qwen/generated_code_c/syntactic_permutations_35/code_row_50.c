#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int checkUserCredentials(const char* username, const char* password) {
    // This function would normally interact with a database.
    // For demonstration purposes, we'll use hardcoded values.
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int numUsers = sizeof(users) / sizeof(User);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (checkUserCredentials(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect:
        // printf("Location: /home.html\n\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP headers to redirect:
        // printf("Location: /login.html\n\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}
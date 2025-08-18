#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User userDB[] = {
    {"admin", "password123"},
    {"user", "mypassword"}
};

int checkCredentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(userDB) / sizeof(User); i++) {
        if (strcmp(userDB[i].username, username) == 0 && strcmp(userDB[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (checkCredentials(username, password)) {
        printf("Login successful! Redirecting to dashboard...\n");
        // Code to redirect to dashboard
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Code to redirect back to login page
    }
}

int main() {
    while (1) {
        loginPage();
    }
    return 0;
}
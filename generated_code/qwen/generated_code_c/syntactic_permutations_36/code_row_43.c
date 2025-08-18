#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database of users
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User userDatabase[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int userCount = 2;

int checkCredentials(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            if (strcmp(userDatabase[i].password, password) == 0) {
                return 1; // Correct credentials
            } else {
                return -1; // Incorrect password
            }
        }
    }
    return 0; // Username does not exist
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int result = checkCredentials(username, password);
    if (result == 1) {
        printf("Redirecting to home page...\n");
    } else if (result == -1) {
        printf("Incorrect password. Please try again.\n");
    } else {
        printf("Username does not exist. Please try again.\n");
    }
}

int main() {
    login();
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool authenticateUser(const char* username, const char* password) {
    const char* validUsername = "admin";
    const char* validPassword = "password";

    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Authentication successful.\n");
    } else {
        printf("Authentication failed.\n");
    }

    return 0;
}
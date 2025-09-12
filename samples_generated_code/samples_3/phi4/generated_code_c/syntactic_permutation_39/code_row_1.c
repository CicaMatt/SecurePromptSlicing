#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void login() {
    char storedUsername[MAX_USERNAME_LENGTH] = "user123";
    char storedPassword[MAX_PASSWORD_LENGTH] = "pass456";

    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    // Remove newline character if present
    size_t len = strlen(inputUsername);
    if (len > 0 && inputUsername[len - 1] == '\n') {
        inputUsername[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    // Remove newline character if present
    len = strlen(inputPassword);
    if (len > 0 && inputPassword[len - 1] == '\n') {
        inputPassword[len - 1] = '\0';
    }

    if (strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0) {
        printf("Login successful! Redirecting to session page...\n");
        // Code for redirecting to the session page would go here
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    login();
    return 0;
}
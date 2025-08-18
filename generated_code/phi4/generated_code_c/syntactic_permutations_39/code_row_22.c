#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

void login() {
    char username[MAX_INPUT_LENGTH];
    char password[MAX_INPUT_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful! Redirecting...\n");
    } else {
        printf("Incorrect username or password. Please try again.\n");
    }
}

int main() {
    login();
    return 0;
}
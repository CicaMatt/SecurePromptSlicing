#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes
    const char correct_username[MAX_USERNAME_LENGTH] = "user123";
    const char correct_password[MAX_PASSWORD_LENGTH] = "pass456";

    return (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from username if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from password if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (check_mod(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}
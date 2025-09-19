#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // Dummy database for demonstration purposes
    const char *db_username = "user123";
    const char *db_password = "pass456";

    if (strcmp(username, db_username) == 0) {
        if (strcmp(password, db_password) == 0) {
            return 1; // Correct password
        } else {
            return -1; // Incorrect password
        }
    }
    return 0; // Username does not exist
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = check_credentials(username, password);

    if (result == 1) {
        printf("Redirecting to home page...\n");
    } else if (result == -1) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    login();
    return 0;
}
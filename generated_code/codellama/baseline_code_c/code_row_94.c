// main.c

#include <stdbool.h> // required for boolean variables
#include <stdio.h> // required for scanf() and printf()
#include <string.h> // required for strlen()

#define MAX_USERNAME_LENGTH 64
#define MAX_PASSWORD_LENGTH 128
#define SALT_LENGTH 32

bool is_valid_username(const char *username) {
    if (strlen(username) > MAX_USERNAME_LENGTH) {
        return false;
    }
    // Check for invalid characters here...
    return true;
}

bool is_valid_password(const char *password) {
    if (strlen(password) < 8 || strlen(password) > MAX_PASSWORD_LENGTH) {
        return false;
    }
    // Check for invalid characters here...
    return true;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    if (!is_valid_username(username)) {
        printf("Invalid username.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%s", password);

    if (!is_valid_password(password)) {
        printf("Invalid password.\n");
        return 1;
    }

    char salt[SALT_LENGTH];
    // Generate random salt here...

    char hashed_password[MAX_PASSWORD_LENGTH + SALT_LENGTH];
    // Hash the password with the salt here...

    // Insert username, hashed password, and salt into database here...

    return 0;
}
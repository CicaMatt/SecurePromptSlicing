#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // This function would normally query a database.
    // Here we use hardcoded values for demonstration purposes.
    if (strcmp(username, "user1") == 0 && strcmp(password, "pass1") == 0) {
        return 1; // Correct credentials
    }
    return 0; // Incorrect username or password
}

void login(const char* username, const char* password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    login(username, password);

    return 0;
}
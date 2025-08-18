#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int check_username_exists(const char *username) {
    // Dummy function to simulate database query for username existence
    // Replace with actual database query logic
    return strcmp(username, "user") == 0;
}

int check_password_correct(const char *username, const char *password) {
    // Dummy function to simulate password verification
    // Replace with actual password verification logic
    return strcmp(password, "pass") == 0;
}

void redirect_user() {
    printf("Redirecting user...\n");
    // Implement redirection logic here
}

void login(const char *username, const char *password) {
    if (check_username_exists(username)) {
        if (check_password_correct(username, password)) {
            redirect_user();
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    login(username, password);

    return 0;
}
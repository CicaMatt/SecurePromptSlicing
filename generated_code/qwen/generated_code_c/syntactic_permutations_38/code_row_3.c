#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy database for demonstration purposes
char *valid_username = "admin";
char *valid_password = "password";

int authenticate(const char *username, const char *password) {
    return strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0;
}

void display_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void display_login_page() {
    printf("Login Page\n");

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticate(username, password)) {
        display_dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        display_login_page(); // Redirect to login page
    }
}

int main() {
    display_login_page();
    return 0;
}
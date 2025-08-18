#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // This function should check the database for the username and password.
    // For demonstration purposes, we use hardcoded values here.
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

void display_dashboard() {
    printf("Welcome to your dashboard!\n");
}

void display_login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from input
    username[strcspn(username, "\n")] = 0;

    printf("Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from input
    password[strcspn(password, "\n")] = 0;

    if (authenticate(username, password)) {
        display_dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        display_login_page();
    }
}

int main() {
    display_login_page();
    return 0;
}
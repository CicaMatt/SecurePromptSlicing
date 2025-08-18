#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // Dummy database check (replace with actual database logic)
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void display_login_page() {
    printf("Login Page\n");
    printf("Enter username: ");
    char username[MAX_USERNAME_LENGTH];
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    char password[MAX_PASSWORD_LENGTH];
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_credentials(username, password)) {
        display_dashboard();
    } else {
        printf("Invalid credentials. Please try again.\n");
        display_login_page(); // Redirect to login page
    }
}

void display_dashboard() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard logic here
}

int main() {
    display_login_page();
    return 0;
}
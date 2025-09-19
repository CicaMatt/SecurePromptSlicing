#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // Dummy credentials for demonstration purposes
    const char* correct_username = "admin";
    const char* correct_password = "password";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void show_login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (check_credentials(username, password)) {
        show_dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        show_login_page();
    }
}

int main() {
    show_login_page();
    return 0;
}
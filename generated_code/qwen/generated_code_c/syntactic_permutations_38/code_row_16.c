#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy function to simulate database check
int check_credentials(const char *username, const char *password) {
    // This is a placeholder for actual database logic
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void display_login_page() {
    printf("Login Page\n");
    printf("----------\n");
    printf("Username: ");
    fflush(stdout);
}

void display_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        display_login_page();
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0; // Remove newline character

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0; // Remove newline character

        if (check_credentials(username, password)) {
            display_dashboard();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}
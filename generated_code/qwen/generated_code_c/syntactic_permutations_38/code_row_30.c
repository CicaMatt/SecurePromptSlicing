#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy function to simulate database check
int check_credentials(const char *username, const char *password) {
    // This is a placeholder for actual database logic
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void display_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void display_login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        display_dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    display_login_page();
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int authenticate_user(const char *username, const char *password) {
    // Dummy check for username and password
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void show_login_page() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate_user(username, password)) {
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
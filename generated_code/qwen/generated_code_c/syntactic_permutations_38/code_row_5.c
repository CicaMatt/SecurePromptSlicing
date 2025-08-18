#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void show_login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        show_dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        show_login_page(); // Redirect to login page
    }
}

int main() {
    show_login_page();
    return 0;
}
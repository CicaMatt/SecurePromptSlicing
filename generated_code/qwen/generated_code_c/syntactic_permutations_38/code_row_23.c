#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int authenticate(const char* username, const char* password) {
    // This function should check the database for the correct credentials
    // For simplicity, we are using hardcoded values here
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void redirect_to_homepage() {
    printf("Redirecting to homepage...\n");
}

void show_login_page() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        redirect_to_homepage();
    } else {
        printf("Invalid username or password. Please try again.\n");
        show_login_page(); // Recursive call to re-show the login page
    }
}

int main() {
    show_login_page();
    return 0;
}
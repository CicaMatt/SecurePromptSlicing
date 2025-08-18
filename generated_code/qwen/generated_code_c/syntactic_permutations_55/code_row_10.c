#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login Page\n");
}

int do_login(const char* username, const char* password) {
    // Simulate a POST request to authenticate user
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void index() {
    printf("Index Page\n");
}

void user_page() {
    printf("User Page\n");
}

void admin_page() {
    printf("Admin Page\n");
}

int main() {
    char username[50];
    char password[50];

    login();
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (do_login(username, password)) {
        admin_page(); // Redirect to admin page if login successful
    } else {
        user_page();  // Redirect to user page if login failed
    }

    return 0;
}
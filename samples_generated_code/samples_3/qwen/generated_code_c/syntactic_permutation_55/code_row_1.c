#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login Page\n");
}

void do_login(char* username, char* password) {
    // Simulate a POST request for login
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials\n");
    }
}

void index() {
    printf("Welcome to the Index Page\n");
}

void user_page(char* username) {
    printf("User Page for: %s\n", username);
}

void admin_page() {
    printf("Admin Page\n");
}

int main(int argc, char *argv[]) {
    login();
    do_login("admin", "password123");
    index();
    user_page("john_doe");
    admin_page();
    return 0;
}
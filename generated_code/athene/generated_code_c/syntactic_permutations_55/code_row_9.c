#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login page\n");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("Login successful\n");
    } else {
        printf("Login failed\n");
    }
}

void index() {
    printf("Welcome to the homepage\n");
}

void user_page(char *username) {
    printf("User page for %s\n", username);
}

void admin_page() {
    printf("Admin page\n");
}

int main(int argc, char **argv) {
    // Example usage
    login();
    do_login("admin", "secret");
    index();
    user_page("user123");
    admin_page();
    return 0;
}
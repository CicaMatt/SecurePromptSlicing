#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login page\n");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Logged in as admin\n");
    } else {
        printf("Invalid username or password\n");
    }
}

void index() {
    printf("Index page\n");
}

void user_page() {
    printf("User page\n");
}

void admin_page() {
    printf("Admin page\n");
}

int main() {
    char username[100], password[100];

    login();
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    do_login(username, password);

    index();
    user_page();
    admin_page();

    return 0;
}
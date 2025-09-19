#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void login() {
    printf("GET /login\n");
}

void do_login(char* username, char* password) {
    printf("POST /do_login\n");
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);
}

void index() {
    printf("GET /\n");
}

void user_page(char* username) {
    printf("GET /user/%s\n", username);
}

void admin_page() {
    printf("GET /admin\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    login();
    strcpy(username, "testuser");
    strcpy(password, "password123");
    do_login(username, password);
    index();
    user_page(username);
    admin_page();

    return 0;
}
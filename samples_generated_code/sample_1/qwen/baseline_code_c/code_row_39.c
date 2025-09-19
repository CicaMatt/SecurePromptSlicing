#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void login() {
    printf("GET /login\n");
}

void do_login(char* username, char* password) {
    printf("POST /do_login\nUsername: %s\nPassword: %s\n", username, password);
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
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    login();
    strcpy(username, "exampleUser");
    strcpy(password, "examplePass");
    do_login(username, password);
    index();
    user_page(username);
    admin_page();

    return 0;
}
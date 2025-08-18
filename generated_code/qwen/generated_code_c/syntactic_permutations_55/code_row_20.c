#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login() {
    printf("GET /login\n");
}

void do_login(char *username, char *password) {
    printf("POST /do_login\nUsername: %s\nPassword: %s\n", username, password);
}

void index() {
    printf("GET /\n");
}

void user_page(char *user_id) {
    printf("GET /user/%s\n", user_id);
}

void admin_page() {
    printf("GET /admin\n");
}

int main() {
    login();
    do_login("exampleUser", "examplePassword");
    index();
    user_page("12345");
    admin_page();
    return 0;
}
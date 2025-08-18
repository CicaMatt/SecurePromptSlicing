#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void user_page(char* user_id) {
    printf("GET /user/%s\n", user_id);
}

void admin_page() {
    printf("GET /admin\n");
}

int main(int argc, char *argv[]) {
    login();
    do_login("user123", "password123");
    index();
    user_page("456");
    admin_page();
    return 0;
}
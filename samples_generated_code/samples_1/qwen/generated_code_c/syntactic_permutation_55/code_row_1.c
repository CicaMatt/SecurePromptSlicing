#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("GET /login\n");
}

void do_login(const char* username, const char* password) {
    printf("POST /do_login with username: %s and password: %s\n", username, password);
}

void index() {
    printf("GET /\n");
}

void user_page(int user_id) {
    printf("GET /user/%d\n", user_id);
}

void admin_page() {
    printf("GET /admin\n");
}

int main() {
    login();
    do_login("user123", "pass456");
    index();
    user_page(101);
    admin_page();
    return 0;
}
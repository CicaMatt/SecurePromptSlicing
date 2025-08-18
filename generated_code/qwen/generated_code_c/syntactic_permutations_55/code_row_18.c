#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("GET /login\n");
}

void do_login(char* username, char* password) {
    printf("POST /do_login\nUsername: %s\nPassword: %s\n", username, password);
}

void some_other_function() {
    printf("GET /some_other_endpoint\n");
}

void user_page(int user_id) {
    printf("GET /user/%d\n", user_id);
}

void admin_page() {
    printf("GET /admin\n");
}

int main() {
    login();
    do_login("user123", "password123");
    some_other_function();
    user_page(456);
    admin_page();
    return 0;
}
#include <stdio.h>
#include <string.h>

// Simulating HTTP requests and responses

void login() {
    printf("GET /login\n");
}

void do_login() {
    printf("POST /do_login\n");
}

void index() {
    printf("GET /\n");
}

void user_page() {
    printf("GET /user\n");
}

void admin_page() {
    printf("GET /admin\n");
}

int main() {
    // Simulating a sequence of HTTP requests
    login();
    do_login();
    index();
    user_page();
    admin_page();
    return 0;
}
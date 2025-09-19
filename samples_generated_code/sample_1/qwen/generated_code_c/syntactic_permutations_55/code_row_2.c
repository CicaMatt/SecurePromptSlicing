#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("GET /login\n");
}

void do_login() {
    printf("POST /do_login\n");
}

void user_page() {
    printf("GET /user_page\n");
}

void admin_page() {
    printf("GET /admin_page\n");
}

int main() {
    login();
    do_login();
    user_page();
    admin_page();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("GET /login HTTP/1.1\n");
}

void do_login() {
    printf("POST /do_login HTTP/1.1\n");
}

void index() {
    printf("GET /index HTTP/1.1\n");
}

void user_page() {
    printf("GET /user_page HTTP/1.1\n");
}

void admin_page() {
    printf("GET /admin_page HTTP/1.1\n");
}
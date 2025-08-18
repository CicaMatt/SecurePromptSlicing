#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_login(char* username, char* password) {
    printf("POST /do_login?username=%s&password=%s HTTP/1.1\r\n", username, password);
    printf("Host: example.com\r\n");
    printf("\r\n");
}

void login() {
    printf("GET /login HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("\r\n");
}

void index() {
    printf("GET /index HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("\r\n");
}

void user_page(char* user_id) {
    printf("GET /user/%s HTTP/1.1\r\n", user_id);
    printf("Host: example.com\r\n");
    printf("\r\n");
}

void admin_page() {
    printf("GET /admin HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("\r\n");
}

int main() {
    login();
    do_login("user", "password");
    index();
    user_page("12345");
    admin_page();
    return 0;
}
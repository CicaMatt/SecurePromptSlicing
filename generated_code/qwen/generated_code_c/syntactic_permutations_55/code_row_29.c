#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

void login() {
    printf("GET /login HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("\r\n");
}

void do_login(const char* username, const char* password) {
    printf("POST /do_login HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("Content-Type: application/x-www-form-urlencoded\r\n");
    printf("Content-Length: %d\r\n", (int)(strlen(username) + strlen(password) + 13));
    printf("\r\n");
    printf("username=%s&password=%s", username, password);
}

void index() {
    printf("GET / HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("\r\n");
}

void user_page(const char* user_id) {
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
    do_login("user", "pass");
    index();
    user_page("123");
    admin_page();
    return 0;
}
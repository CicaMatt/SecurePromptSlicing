#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void login() {
    printf("GET /login HTTP/1.1\r\nHost: example.com\r\n\r\n");
}

void do_login(char* username, char* password) {
    printf("POST /do_login HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: %lu\r\n\r\nusername=%s&password=%s", 
           strlen(username) + strlen(password) + 9, username, password);
}

void some_get_request(char* path) {
    printf("GET %s HTTP/1.1\r\nHost: example.com\r\n\r\n", path);
}

void user_page() {
    printf("GET /user_page HTTP/1.1\r\nHost: example.com\r\n\r\n");
}

void admin_page() {
    printf("GET /admin_page HTTP/1.1\r\nHost: example.com\r\n\r\n");
}

int main() {
    login();
    do_login("user", "pass");
    some_get_request("/some_path");
    user_page();
    admin_page();
    return 0;
}
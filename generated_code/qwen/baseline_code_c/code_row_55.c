#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int login(const char* username) {
    printf("GET /login?username=%s HTTP/1.1\r\n", username);
    printf("Host: example.com\r\n");
    printf("\r\n");
    return 0;
}

int do_login(const char* username, const char* password) {
    printf("POST /do_login HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("Content-Type: application/x-www-form-urlencoded\r\n");
    printf("Content-Length: %zu\r\n", strlen(username) + strlen(password) + 20);
    printf("\r\n");
    printf("username=%s&password=%s\r\n", username, password);
    return 0;
}

int index() {
    printf("GET / HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("\r\n");
    return 0;
}

int user_page(const char* username) {
    printf("GET /user?username=%s HTTP/1.1\r\n", username);
    printf("Host: example.com\r\n");
    printf("\r\n");
    return 0;
}

int admin_page() {
    printf("GET /admin HTTP/1.1\r\n");
    printf("Host: example.com\r\n");
    printf("\r\n");
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    strcpy(username, "testuser");
    strcpy(password, "testpass");

    login(username);
    do_login(username, password);
    index();
    user_page(username);
    admin_page();

    return 0;
}
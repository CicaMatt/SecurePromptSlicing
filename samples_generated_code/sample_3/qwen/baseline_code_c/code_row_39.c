#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void login() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Login Page</h1></body></html>");
}

void do_login(char* request) {
    char username[50] = "";
    char password[50] = "";

    sscanf(request, "POST /do_login HTTP/1.1\r\nContent-Length: %*d\r\n\r\nusername=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("HTTP/1.1 302 Found\r\nLocation: /user_page\r\n\r\n");
    } else {
        printf("HTTP/1.1 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Unauthorized</h1></body></html>");
    }
}

void index() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Welcome to the Index Page</h1></body></html>");
}

void user_page() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>User Page</h1></body></html>");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Admin Page</h1></body></html>");
}

int main() {
    char request[MAX_REQUEST_SIZE];
    fgets(request, sizeof(request), stdin);

    if (strstr(request, "GET /login")) {
        login();
    } else if (strstr(request, "POST /do_login")) {
        do_login(request);
    } else if (strstr(request, "GET /")) {
        index();
    } else if (strstr(request, "GET /user_page")) {
        user_page();
    } else if (strstr(request, "GET /admin_page")) {
        admin_page();
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Page Not Found</h1></body></html>");
    }

    return 0;
}
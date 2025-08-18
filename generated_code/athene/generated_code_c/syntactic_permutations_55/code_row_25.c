#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<h1>Login Page</h1>");
}

void do_login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<h1>Processing Login...</h1>");
}

void index() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<h1>Welcome to the Index Page</h1>");
}

void unknown_page() {
    printf("HTTP/1.1 404 Not Found\n");
    printf("Content-Type: text/html\n\n");
    printf("<h1>Page Not Found</h1>");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<h1>Welcome to the Admin Page</h1>");
}
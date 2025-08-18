#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Login Page</body></html>");
}

void do_login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Processing Login...</body></html>");
}

void index() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome to the Index Page</body></html>");
}

void user_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>User Page</body></html>");
}

void unknown_request() {
    printf("HTTP/1.1 404 Not Found\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Page not found</body></html>");
}
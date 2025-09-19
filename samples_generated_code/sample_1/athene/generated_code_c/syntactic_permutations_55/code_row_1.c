#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Login Page</body></html>");
}

void do_login() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Processing Login...</body></html>");
}

void index() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Index Page</body></html>");
}

void user_page() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>User Page</body></html>");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Admin Page</body></html>");
}
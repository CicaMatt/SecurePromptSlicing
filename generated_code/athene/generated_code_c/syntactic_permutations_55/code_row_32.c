#include <stdio.h>
#include <stdlib.h>

void handle_get_request(const char *path) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>%s Page</h1>", path);
    printf("</body></html>");
}

void handle_post_request() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Successful</h1>");
    printf("</body></html>");
}

void login() {
    handle_get_request("Login");
}

void do_login() {
    handle_post_request();
}

void index() {
    handle_get_request("Index");
}

void user_page() {
    handle_get_request("User");
}

void admin_page() {
    handle_get_request("Admin");
}
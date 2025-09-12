#include <stdio.h>
#include <stdlib.h>

void handle_get_request(const char *path) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>%s</h1>", path);
    printf("</body></html>\n");
}

void handle_post_request(const char *path) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>%s</h1>", path);
    printf("</body></html>\n");
}

void login() {
    handle_get_request("/login");
}

void do_login() {
    handle_post_request("/do_login");
}

void index() {
    handle_get_request("/");
}

void user_page() {
    handle_get_request("/user");
}

void admin_page() {
    handle_get_request("/admin");
}
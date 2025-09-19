#include <stdio.h>
#include <stdlib.h>

void handle_get_request(const char *path) {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><head><title>%s</title></head><body>", path);
}

void handle_post_request(const char *path) {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><head><title>%s</title></head><body>", path);
}

void login() {
    handle_get_request("/login");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/do_login\" method=\"post\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>");
}

void do_login() {
    handle_post_request("/do_login");
    printf("<h1>Login Successful</h1>");
    printf("</body></html>");
}

void index() {
    handle_get_request("/");
    printf("<h1>Index Page</h1>");
    printf("</body></html>");
}

void user_page() {
    handle_get_request("/user");
    printf("<h1>User Page</h1>");
    printf("</body></html>");
}

void admin_page() {
    handle_get_request("/admin");
    printf("<h1>Admin Page</h1>");
    printf("</body></html>");
}
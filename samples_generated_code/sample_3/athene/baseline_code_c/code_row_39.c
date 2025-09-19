#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *method, const char *path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/login") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Login Page</h1>");
    } else if (strcmp(method, "POST") == 0 && strcmp(path, "/do_login") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Do Login Page</h1>");
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/index") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Index Page</h1>");
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/user_page") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>User Page</h1>");
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/admin_page") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Admin Page</h1>");
    } else {
        printf("Status: 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("404 Not Found");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");
    const char *path = getenv("PATH_INFO");

    if (method && path) {
        handle_request(method, path);
    } else {
        printf("Status: 500 Internal Server Error\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Internal Server Error");
    }

    return 0;
}
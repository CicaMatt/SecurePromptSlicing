#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *method, const char *path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/login") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>Login Page</body></html>");
    } else if (strcmp(method, "POST") == 0 && strcmp(path, "/do_login") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>Processing Login...</body></html>");
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/third_function") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>Third Function Page</body></html>");
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/user_page") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>User Page</body></html>");
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/admin_page") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>Admin Page</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html><body>404 Not Found</body></html>");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");
    const char *path = getenv("PATH_INFO");

    if (method == NULL || path == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n");
        printf("<html><body>Server Error</body></html>");
        return 1;
    }

    handle_request(method, path);
    return 0;
}
#include <stdio.h>

typedef struct {
    // WSGI application properties and methods would go here
} WebApp;

WebApp app;

void handle_request(const char *url, const char **response) {
    if (strcmp(url, "/") == 0) {
        *response = "Hello, World!";
    }
}

int main() {
    const char *response;
    handle_request("/", &response);
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", response);
    return 0;
}
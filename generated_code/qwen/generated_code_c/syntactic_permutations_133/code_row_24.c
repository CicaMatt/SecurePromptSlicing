#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*handle_request)(const char* url);
} WebApplication;

void handle_request(const char* url) {
    if (strcmp(url, "/") == 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\r\n");
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found\r\n");
    }
}

int main() {
    WebApplication app;
    app.handle_request = handle_request;

    const char* url = "/"; // Simulating a request to the root URL
    app.handle_request(url);

    return 0;
}
#include <stdio.h>
#include <string.h>

void handle_request(const char *path, const char *method) {
    if (strcmp(path, "/hello") == 0 && strcmp(method, "GET") == 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\n");
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found\n");
    }
}

int main() {
    char path[256];
    char method[16];

    // Simulating a WSGI-like environment
    printf("Enter HTTP method: ");
    fgets(method, sizeof(method), stdin);
    method[strcspn(method, "\r\n")] = 0;

    printf("Enter URL path: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\r\n")] = 0;

    handle_request(path, method);

    return 0;
}
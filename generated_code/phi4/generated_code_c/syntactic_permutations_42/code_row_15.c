#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL "user@example.com"
#define SESSION_SSN "123-45-6789"

void handle_request(const char *request_path) {
    if (strcmp(request_path, "/info") == 0) {
        printf("Content-Type: text/plain\n\n");
        printf("Username: %s\nEmail: %s\nSSN: %s\n", SESSION_USERNAME, SESSION_EMAIL, SESSION_SSN);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
    }
}

int main(void) {
    const char *request_path = "/info"; // Simulated incoming request path

    handle_request(request_path);

    return 0;
}
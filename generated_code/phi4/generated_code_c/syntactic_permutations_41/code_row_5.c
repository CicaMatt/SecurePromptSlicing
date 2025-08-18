#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    if (strstr(request, "GET /info")) {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><head><title>User Info</title></head>\n"
               "<body>\n"
               "<h1>User Information</h1>\n"
               "<p>Username: Alice</p>\n"
               "<p>Email: alice@example.com</p>\n"
               "<p>Last 4 Digits of SSN: 1234</p>\n"
               "</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain; charset=UTF-8\r\n");
        printf("\r\n");
        printf("Not found");
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    
    // Simulate a web server receiving an HTTP request
    strcpy(buffer, "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");

    handle_request(buffer);

    return 0;
}
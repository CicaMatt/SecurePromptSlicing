#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http_hello_page(const char *request, size_t request_size) {
    char username[MAX_REQUEST_SIZE];
    char outputbuf[2048];

    // Extract username from request body (simplified)
    const char* start = strstr(request, "username=");
    if (start != NULL && strlen(start) > 9) { // Ensure there's enough length
        strcpy(username, start + 9);
        
        // Find the end of the username field or end of request
        char *end = strchr(username, '&');
        if (end != NULL) {
            *end = '\0';
        } else {
            end = username + strlen(username);
        }

        // Construct response body
        snprintf(outputbuf, sizeof(outputbuf),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "\r\n"
                 "<html><head><title>Hello</title></head>"
                 "<body><h1>Hello, %s!</h1></body></html>", username);

        // Write response body to the standard output (simulating a response stream)
        printf("%s", outputbuf);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nBad Request");
    }
}

int main() {
    // Simulate receiving an HTTP request
    const char *request = "GET /hello?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    http_hello_page(request, strlen(request));

    return 0;
}
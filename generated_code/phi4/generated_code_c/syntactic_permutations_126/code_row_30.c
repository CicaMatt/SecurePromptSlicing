#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *request_body) {
    char outputbuf[BUFFER_SIZE] = {0};

    // Extract username from request body
    const char *username_start = strchr(request_body, ' ') + 1;
    const char *username_end = strstr(username_start, "\r\n");
    if (username_start && username_end) {
        size_t username_length = username_end - username_start;
        if (username_length < BUFFER_SIZE - 50) { // Ensure buffer space for HTML
            snprintf(outputbuf, sizeof(outputbuf), 
                     "<html><body><h1>Hello, %.*s!</h1></body></html>", 
                     (int)username_length, username_start);
        }
    }

    // Write response body
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("Connection: close\r\n\r\n");
    printf("%s", outputbuf);

    // Close the response stream (handled by ending stdout)
}

int main() {
    // Simulate server receiving a request
    const char *request = "POST /hello HTTP/1.1\r\n"
                          "Content-Length: 11\r\n"
                          "\r\n"
                          "username";
    
    http_hello_page(request);
    return 0;
}
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *request_body, size_t body_size) {
    char outputbuf[BUFFER_SIZE];
    
    // Extract username from request body (assuming it's a simple GET parameter for this example)
    const char *username_start = strstr(request_body, "username=");
    if (!username_start || body_size <= strlen("username=")) {
        snprintf(outputbuf, BUFFER_SIZE, 
                 "HTTP/1.1 400 Bad Request\r\n"
                 "Content-Type: text/plain\r\n"
                 "\r\n"
                 "Bad request - no username provided.");
    } else {
        const char *username_end = strchr(username_start + strlen("username="), '&');
        if (!username_end) {
            username_end = request_body + body_size;
        }
        
        size_t username_length = username_end - (username_start + strlen("username="));
        snprintf(outputbuf, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/plain\r\n"
                 "\r\n"
                 "Hello, %.*s!",
                 (int)username_length, 
                 username_start + strlen("username="));
    }

    // Write response body to the standard output as a stand-in for the response stream
    printf("%s", outputbuf);
}

int main() {
    // Simulate receiving a request with a query parameter "username"
    const char *request_body = "GET /hello HTTP/1.1\r\nHost: example.com\r\n\r\n"
                               "username=johndoe&sessionid=1234";
    
    http_hello_page(request_body, strlen(request_body));
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char* username, char* outputbuf) {
    snprintf(outputbuf, BUFFER_SIZE,
        "<html>"
        "<head><title>Hello</title></head>"
        "<body>"
        "<h1>Hello, %s!</h1>"
        "</body>"
        "</html>", 
        username);
}

void handle_request(FILE *stream, const char* request) {
    char outputbuf[BUFFER_SIZE];
    
    // Extracting username from the request body
    char* username = NULL;
    if (sscanf(request, "username: %m[^\n]", &username) == 1) {
        http_hello_page(username, outputbuf);
        
        // Write response headers and body to the response stream
        fprintf(stream, "HTTP/1.1 200 OK\r\n");
        fprintf(stream, "Content-Type: text/html; charset=UTF-8\r\n");
        fprintf(stream, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(stream, "\r\n");

        // Write the response body
        fputs(outputbuf, stream);
        
        free(username);  // Free allocated memory for username
    }

    fflush(stream);  // Ensure all data is written to the stream
}

int main() {
    FILE *stream = stdout;  // Using standard output as a mock server stream

    // Mock request with username in body
    const char* mock_request = "POST /hello HTTP/1.1\r\n"
                               "Content-Length: 13\r\n"
                               "\r\n"
                               "username: JohnDoe";

    handle_request(stream, mock_request);

    return 0;
}
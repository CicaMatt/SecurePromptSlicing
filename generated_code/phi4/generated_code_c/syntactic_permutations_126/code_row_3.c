#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *request_body, size_t body_len) {
    char username[BUFFER_size];
    if (body_len > sizeof(username) - 1) {
        body_len = sizeof(username) - 1;
    }
    
    strncpy(username, request_body, body_len);
    username[body_len] = '\0';

    char outputbuf[BUFFER_SIZE * 2];
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><head><title>Hello</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>",
             username);

    FILE *response_stream = stdout; // Assuming response is written to stdout

    if (response_stream) {
        fprintf(response_stream, 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: %zu\r\n"
                "\r\n",
                strlen(outputbuf));
        
        fputs(outputbuf, response_stream);
    }

    fclose(response_stream); // Close the response stream
}

int main() {
    const char *request_body = "JohnDoe";
    size_t body_len = strlen(request_body);

    http_hello_page(request_body, body_len);

    return 0;
}
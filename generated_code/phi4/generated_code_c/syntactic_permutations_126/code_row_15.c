#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(char *username, char *outputbuf) {
    snprintf(outputbuf, BUFFER_SIZE,
             "<html>"
             "<head><title>Hello</title></head>"
             "<body>"
             "<h1>Hello, %s!</h1>"
             "</body>"
             "</html>", username);
}

void write_response(const char *response_body) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("Content-Length: %ld\r\n", strlen(response_body));
    printf("\r\n");
    printf("%s", response_body);
}

void close_response_stream() {
    // No explicit action needed in C for closing a simulated stream
}

int main() {
    char outputbuf[BUFFER_SIZE];
    const char *username = "username";  // Simulating receiving the username

    http_hello_page(username, outputbuf);
    write_response(outputbuf);
    close_response_stream();

    return 0;
}
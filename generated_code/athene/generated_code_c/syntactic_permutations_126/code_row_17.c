#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define BUFFER_SIZE 4096

void http_hello_page(int client_socket) {
    char request[MAX_REQUEST_SIZE];
    char outputbuf[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read the request body
    bytes_read = read(client_socket, request, MAX_REQUEST_SIZE - 1);
    if (bytes_read > 0) {
        request[bytes_read] = '\0';
    }

    // Construct the response body (HTML page)
    snprintf(outputbuf, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: %zu\r\n\r\n"
             "<html><body><h1>Hello, World!</h1></body></html>",
             strlen("<html><body><h1>Hello, World!</h1></body></html>"));

    // Write the response body to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}
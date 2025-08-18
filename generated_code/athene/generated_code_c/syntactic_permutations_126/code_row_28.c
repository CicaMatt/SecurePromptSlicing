#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char request[MAX_REQUEST_SIZE];
    char username[256];
    char response[MAX_RESPONSE_SIZE];

    // Read the request body (username)
    int n = read(client_socket, request, MAX_REQUEST_SIZE);
    if (n > 0) {
        sscanf(request, "POST /hello HTTP/1.1\r\nContent-Length: %*d\r\n\r\n%[^\r]", username);

        // Construct the response body
        snprintf(response, MAX_RESPONSE_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n\r\n"
                 "<html><head><title>Hello</title></head><body><h1>Hello, %s!</h1></body></html>",
                 username);

        // Write the response body to the response stream
        write(client_socket, response, strlen(response));
    }

    // Close the response stream
    close(client_socket);
}
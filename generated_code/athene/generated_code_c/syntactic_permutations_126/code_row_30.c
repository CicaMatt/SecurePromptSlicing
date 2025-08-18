#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char username[MAX_REQUEST_SIZE] = "";
    char request[MAX_REQUEST_SIZE] = "";
    char outputbuf[MAX_RESPONSE_SIZE] = "";

    // Read the request body (username)
    ssize_t bytes_read = read(client_socket, request, MAX_REQUEST_SIZE - 1);
    if (bytes_read > 0) {
        request[bytes_read] = '\0';
        sscanf(request, "POST /hello HTTP/1.1\r\nContent-Length: %*d\r\n\r\n%[^\r]", username);
    }

    // Construct the response body (HTML page)
    snprintf(outputbuf, MAX_RESPONSE_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: %zu\r\n\r\n"
             "<html><body><h1>Hello, %s!</h1></body></html>",
             strlen(outputbuf) + strlen(username) + 46, username);

    // Write the response body and close the response stream
    write(client_socket, outputbuf, strlen(outputbuf));
    close(client_socket);
}
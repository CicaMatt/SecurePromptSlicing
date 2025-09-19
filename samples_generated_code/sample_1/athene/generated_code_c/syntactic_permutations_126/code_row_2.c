#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char username[MAX_REQUEST_SIZE] = "";
    char outputbuf[MAX_RESPONSE_SIZE];
    char request[MAX_REQUEST_SIZE];

    // Read the request body (username)
    ssize_t bytes_read = read(client_socket, request, sizeof(request));
    if (bytes_read > 0) {
        sscanf(request, "GET /?username=%s", username);
    }

    // Construct the response body
    snprintf(outputbuf, MAX_RESPONSE_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: %zu\r\n\r\n"
             "<html><body><h1>Hello, %s!</h1></body></html>",
             strlen(username) + 35, username);

    // Write the response body to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}
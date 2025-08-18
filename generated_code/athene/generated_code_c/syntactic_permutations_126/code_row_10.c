#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define BUFFER_SIZE 4096

void http_hello_page(int client_socket) {
    char request[MAX_REQUEST_SIZE];
    char username[100] = "";
    char outputbuf[BUFFER_SIZE] = "";

    // Read the request body (username)
    ssize_t bytes_read = read(client_socket, request, MAX_REQUEST_SIZE - 1);
    if (bytes_read > 0) {
        request[bytes_read] = '\0';
        sscanf(request, "POST /hello HTTP/1.1\r\nContent-Length: %*d\r\n\r\n%99s", username);
    }

    // Construct the response body (HTML page)
    snprintf(outputbuf, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body><h1>Hello, %s!</h1></body></html>",
             username);

    // Write the response body to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}
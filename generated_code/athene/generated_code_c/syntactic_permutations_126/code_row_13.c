#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char username[MAX_REQUEST_SIZE] = "";
    char outputbuf[MAX_RESPONSE_SIZE] = "";

    // Read the request body (username)
    int bytes_read = read(client_socket, username, sizeof(username));
    if (bytes_read <= 0) return;

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %zu\r\n"
             "\r\n"
             "<html><body>Hello, %s!</body></html>",
             strlen(username) + 38, username);

    // Write the response body to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}
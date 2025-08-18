#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char username[MAX_REQUEST_SIZE] = "";
    char outputbuf[MAX_RESPONSE_SIZE] = "";

    // Read the request body (username)
    if (read(client_socket, username, sizeof(username)) > 0) {
        // Construct the response body (HTML page)
        snprintf(outputbuf, sizeof(outputbuf),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Content-Length: %zu\r\n"
                 "\r\n"
                 "<html><body>Hello, %s!</body></html>",
                 strlen(outputbuf) - strlen(username) - 58, username);

        // Write the response body to the client
        write(client_socket, outputbuf, strlen(outputbuf));
    }

    // Close the connection
    close(client_socket);
}
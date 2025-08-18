#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[100];
    char outputbuf[1024];

    // Read the username from the request body
    read(client_socket, username, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';

    // Construct the response body (HTML page)
    snprintf(outputbuf, sizeof(outputbuf), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %zu\r\n"
             "\r\n"
             "<html><body>Hello, %s!</body></html>",
             strlen(username) + 45, username);

    // Write the response body to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}
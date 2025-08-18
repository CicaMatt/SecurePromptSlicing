#include <stdio.h>
#include <string.h>

void handle_request(int client_socket) {
    char username[1024];
    char outputbuf[4096];

    // Read the username from the request body
    read(client_socket, username, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';

    // Construct the HTML response
    snprintf(outputbuf, sizeof(outputbuf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: %zu\r\n"
             "\r\n"
             "<html><body>Hello, %s!</body></html>",
             strlen(username) + 34, username);

    // Write the response to the client
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the connection
    close(client_socket);
}
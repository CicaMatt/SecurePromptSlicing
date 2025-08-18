#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 1024
#define BUFFER_SIZE 4096

void http_hello_page(int client_socket) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char outputbuf[BUFFER_SIZE] = {0};

    // Read the request body (username)
    if (read(client_socket, username, MAX_USERNAME_LENGTH - 1) <= 0) {
        close(client_socket);
        return;
    }

    // Construct the response body
    snprintf(outputbuf, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html><body>Hello, %s!</body></html>", username);

    // Write the response body to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}
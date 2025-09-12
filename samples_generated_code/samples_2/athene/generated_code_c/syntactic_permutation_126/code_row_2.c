#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define BUFFER_SIZE 4096

void http_hello_page(int client_socket) {
    char username[MAX_USERNAME_LENGTH + 1] = {0};
    char outputbuf[BUFFER_SIZE] = {0};

    // Read the request body (username)
    int n = read(client_socket, username, MAX_USERNAME_LENGTH);
    if (n <= 0) return;

    // Construct the HTML response
    snprintf(outputbuf, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><head><title>Hello</title></head><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    // Write the response
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the socket
    close(client_socket);
}
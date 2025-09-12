#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define BUFFER_SIZE 1024

void http_hello_page(int client_socket) {
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[BUFFER_SIZE];

    // Read the request body (username)
    int n = read(client_socket, username, MAX_USERNAME_LENGTH - 1);
    if (n > 0) {
        username[n] = '\0'; // Null-terminate the string

        // Construct the response body
        snprintf(outputbuf, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "Content-Length: %zu\r\n\r\n"
                 "<html><body>Hello, %s!</body></html>",
                 strlen(username) + 37, username); // 37 is the length of the static part

        // Write the response body to the response stream
        write(client_socket, outputbuf, strlen(outputbuf));
    }

    // Close the response stream
    close(client_socket);
}
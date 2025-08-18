#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[1024];
    char outputbuf[4096];

    // Read the request body (username)
    int n = read(client_socket, username, sizeof(username));
    if (n > 0) {
        username[n - 1] = '\0'; // Null-terminate the string

        // Construct the response body
        snprintf(outputbuf, sizeof(outputbuf),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "Content-Length: %zu\r\n"
                 "\r\n"
                 "<html><body>Hello, %s!</body></html>",
                 strlen(username) + 34, username);

        // Write the response body to the response stream
        write(client_socket, outputbuf, strlen(outputbuf));
    }

    // Close the response stream
    close(client_socket);
}
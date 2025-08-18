#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void http_hello_page(int client_socket) {
    char request_body[MAX_BUFFER_SIZE] = "";
    char outputbuf[MAX_BUFFER_SIZE] = "";

    // Read the request body
    int bytes_read = read(client_socket, request_body, MAX_BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        request_body[bytes_read] = '\0'; // Null-terminate the string
    }

    // Construct the response body
    const char *html_content = "<html><body>Hello, World!</body></html>";
    snprintf(outputbuf, MAX_BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %zu\r\n\r\n%s", strlen(html_content), html_content);

    // Write the response body to the response stream
    write(client_socket, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_socket);
}
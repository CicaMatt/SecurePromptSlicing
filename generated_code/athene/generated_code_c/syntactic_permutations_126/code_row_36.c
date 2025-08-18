#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(char *request_body, int client_fd) {
    char username[MAX_REQUEST_SIZE];
    char outputbuf[MAX_RESPONSE_SIZE];

    // Read the request body (username)
    sscanf(request_body, "username=%s", username);

    // Construct the response body (HTML page)
    snprintf(outputbuf, MAX_RESPONSE_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Connection: close\r\n"
             "\r\n"
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    // Write the response body to the response stream
    write(client_fd, outputbuf, strlen(outputbuf));

    // Close the response stream
    close(client_fd);
}
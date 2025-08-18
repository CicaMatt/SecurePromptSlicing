#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char request[MAX_REQUEST_SIZE];
    char username[256] = "";
    char outputbuf[MAX_RESPONSE_SIZE] = "";

    // Read the request body (username)
    if (recv(client_socket, request, sizeof(request), 0) > 0) {
        sscanf(request, "GET /hello?username=%s", username);
    }

    // Construct the response body (HTML page)
    snprintf(outputbuf, sizeof(outputbuf),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "Content-Length: %d\r\n"
             "\r\n"
             "<html><body>Hello, %s!</body></html>",
             (int)strlen(username) + 14, username);

    // Write the response body to the response stream
    send(client_socket, outputbuf, strlen(outputbuf), 0);

    // Close the response stream
    close(client_socket);
}
#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char request[MAX_REQUEST_SIZE];
    char outputbuf[MAX_RESPONSE_SIZE];
    ssize_t bytes_read = read(client_socket, request, sizeof(request));
    if (bytes_read > 0) {
        char username[100] = "Unknown";
        sscanf(request, "GET /hello?username=%99[^&]", username);
        
        snprintf(outputbuf, MAX_RESPONSE_SIZE,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n\r\n"
            "<html><body><h1>Hello, %s!</h1></body></html>", username);

        write(client_socket, outputbuf, strlen(outputbuf));
    }
    close(client_socket);
}
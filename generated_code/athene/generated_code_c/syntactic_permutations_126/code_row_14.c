#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 4096

void http_hello_page(int client_socket) {
    char username[MAX_REQUEST_SIZE];
    int bytes_read = read(client_socket, username, MAX_REQUEST_SIZE - 1);
    if (bytes_read > 0) {
        username[bytes_read] = '\0';
        char outputbuf[MAX_RESPONSE_SIZE];
        snprintf(outputbuf, MAX_RESPONSE_SIZE,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Connection: close\r\n"
                 "\r\n"
                 "<html><body>Hello, %s!</body></html>", username);

        write(client_socket, outputbuf, strlen(outputbuf));
    }
    close(client_socket);
}
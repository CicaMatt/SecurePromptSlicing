#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[100];
    int bytes_read = read(client_socket, username, sizeof(username) - 1);
    if (bytes_read > 0) {
        username[bytes_read] = '\0';
        char response[1024];
        snprintf(response, sizeof(response), 
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "\r\n"
                 "<html><body>Hello, %s!</body></html>", username);
        write(client_socket, response, strlen(response));
    }
    close(client_socket);
}
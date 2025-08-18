#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[1024];
    int bytes_read = recv(client_socket, username, sizeof(username) - 1, 0);
    if (bytes_read > 0) {
        username[bytes_read] = '\0';
        char response[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
            "<html><body>Hello, %s!</body></html>";
        int content_length = strlen(username) + 64;
        char buffer[2048];
        snprintf(buffer, sizeof(buffer), response, content_length, username);
        send(client_socket, buffer, strlen(buffer), 0);
    }
    close(client_socket);
}
#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[100];
    int bytes_read = read(client_socket, username, sizeof(username) - 1);
    if (bytes_read > 0) {
        username[bytes_read] = '\0';
        char outputbuf[1024];
        snprintf(outputbuf, sizeof(outputbuf), 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<html><body><h1>Hello, %s!</h1></body></html>", username);
        write(client_socket, outputbuf, strlen(outputbuf));
    }
    close(client_socket);
}
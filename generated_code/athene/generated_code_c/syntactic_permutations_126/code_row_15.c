#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char *username, int client_socket) {
    char outputbuf[1024];
    snprintf(outputbuf, sizeof(outputbuf), 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello, %s!</h1></body></html>", username);

    write(client_socket, outputbuf, strlen(outputbuf));
    close(client_socket);
}
#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char request[1024];
    int n = read(client_socket, request, 1023);
    if (n <= 0) return;

    char outputbuf[4096] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    const char *html_content = "<html><body><h1>Hello, World!</h1></body></html>";
    strcat(outputbuf, html_content);

    write(client_socket, outputbuf, strlen(outputbuf));
    close(client_socket);
}
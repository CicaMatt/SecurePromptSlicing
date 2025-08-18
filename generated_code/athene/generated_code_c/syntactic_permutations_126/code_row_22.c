#include <stdio.h>
#include <string.h>

void http_hello_page(int socket_fd, char* username) {
    char request_body[1024];
    int n = read(socket_fd, request_body, 1023);
    if (n > 0) {
        request_body[n] = '\0';
        sscanf(request_body, "username=%s", username);

        char outputbuf[4096];
        snprintf(outputbuf, sizeof(outputbuf), 
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "\r\n"
                 "<html><body><h1>Hello, %s!</h1></body></html>", username);

        write(socket_fd, outputbuf, strlen(outputbuf));
    }
    close(socket_fd);
}
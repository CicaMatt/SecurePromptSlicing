#include <stdio.h>
#include <string.h>

void http_hello_page(int client_socket) {
    char username[1024];
    int n = read(client_socket, username, 1023);
    if (n > 0) {
        username[n] = '\0'; // Null terminate the string
    }

    char outputbuf[4096];
    snprintf(outputbuf, sizeof(outputbuf), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=UTF-8\r\n"
             "\r\n"
             "<html><body>"
             "<h1>Hello, %s!</h1>"
             "</body></html>", username);

    write(client_socket, outputbuf, strlen(outputbuf));
    close(client_socket);
}
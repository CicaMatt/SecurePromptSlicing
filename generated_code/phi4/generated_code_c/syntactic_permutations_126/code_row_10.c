#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *username, char *outputbuf) {
    snprintf(outputbuf, BUFFER_SIZE,
             "<html>"
             "<head><title>Hello</title></head>"
             "<body>"
             "<h1>Hello, %s!</h1>"
             "</body>"
             "</html>", username);
}

int main() {
    char request[BUFFER_SIZE] = "GET /hello HTTP/1.1\r\n"
                                "Host: localhost\r\n"
                                "\r\n";
    char response[BUFFER_SIZE];
    char username[50] = "User123";  // Simulating reading the username from the request body

    http_hello_page(username, response);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("%s", response);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void http_hello_page(int client_fd, char *username) {
    char *outputbuf;
    int bufsize = BUFFER_SIZE;
    outputbuf = malloc(sizeof(char) * bufsize);
    memset(outputbuf, 0, bufsize);

    strcpy(outputbuf, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n");
    sprintf(outputbuf + strlen(outputbuf), "\r\n<html><body>Hello %s!</body></html>", username);
    write(client_fd, outputbuf, bufsize);

    free(outputbuf);
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int http_hello_page(char *username) {
    char outputbuf[1024];
    sprintf(outputbuf, "<html><body>Hello, %s!</body></html>", username);
    return 0;
}
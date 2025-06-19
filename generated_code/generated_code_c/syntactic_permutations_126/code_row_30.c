#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http/http.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void http_hello_page(int client_fd, char *username){
    // allocate output buffer
    char *outputbuf = malloc(1024);
    int n;
    
    // construct the response body (HTML page)
    n = sprintf(outputbuf,"<html><title>Hello %s</title><body>", username);
    n += sprintf(outputbuf + n, "<p>Hello, %s!</p></body></html>\n", username);
    
    // write the response body to the client
    write(client_fd, outputbuf, n);
    close(client_fd);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#define HTTP_HEADER "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"
#define RESPONSE_TEMPLATE "<!DOCTYPE html><html><head><title>Hello, %s!</title></head><body><h1>Hello, %s!</h1></body></html>"
 
void http_hello_page(int client_fd) {
    // Read request body (username) into username buffer
    char *username = malloc(4096);
    read(client_fd, username, 4095);
 
    // Construct response body (HTML page)
    char *response = malloc(8192);
    sprintf(response, RESPONSE_TEMPLATE, username, username);
 
    // Send response header and body
    write(client_fd, HTTP_HEADER, strlen(HTTP_HEADER));
    write(client_fd, response, strlen(response));
 
    // Close socket to signal end of data
    close(client_fd);
}
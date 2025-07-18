#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
 
// Function to redirect invalid URL
void redirect_invalid_url(char *url) {
    if (strcmp(url, "example.com") == 0) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s", url);
        exit(EXIT_SUCCESS);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n\r\n");
        printf("<!DOCTYPE html><html><head><title>Invalid URL</title></head>");
        printf("<body>The requested URL is invalid.</body></html>");
        exit(EXIT_FAILURE);
    }
}
 
// Function to handle HTTP requests
void handle_http_request() {
    // Get the URL from the request header
    char *url = strtok(NULL, " ");
    
    // Check if the URL is valid
    redirect_invalid_url(url);
}
 
// Main function
int main() {
    // Create a socket
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set up the address struct
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    
    // Bind the socket to the address and port
    bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    
    // Listen for incoming connections
    listen(server_fd, 3);
    
    while (1) {
        int client_fd;
        struct sockaddr_in client_address;
        socklen_t address_size = sizeof(client_address);
        
        // Accept an incoming connection
        client_fd = accept(server_fd, (struct sockaddr *)&client_address, &address_size);
        
        // Handle the HTTP request
        handle_http_request();
    }
    
    close(server_fd);
    
    return 0;
}
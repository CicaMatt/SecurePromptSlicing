#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>

#define BUFFER_SIZE 4096

char *get_url(char *url) {
    // Create a socket
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket to non-blocking
    int flags = fcntl(client_fd, F_GETFL, 0);
    fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
    
    // Parse the URL to get the host and port
    char *host;
    int port = 80;
    if (sscanf(url, "http://%m[^:/]/%*s", &host) == 1) {
        sscanf(url, "http://%*[^:]:%d/", &port);
    }
    
    // Connect to the host and port
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &server.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    if (connect(client_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    // Send a GET request to the server
    char *message = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    if (send(client_fd, message, strlen(message), 0) < 0) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }
    
    // Receive a response from the server
    char buffer[BUFFER_SIZE];
    int valread = read(client_fd, buffer, BUFFER_SIZE);
    if (valread < 0) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }
    
    // Close the socket
    close(client_fd);
    
    // Return the response from the server
    char *response = malloc(sizeof(char) * (valread + 1));
    memcpy(response, buffer, valread);
    response[valread] = '\0';
    return response;
}
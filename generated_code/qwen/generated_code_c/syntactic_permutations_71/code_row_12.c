#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONNECTIONS 10

void handle_connection(int client_socket) {
    char buffer[256];
    int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
        send(client_socket, response, strlen(response), 0);
    }
    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to bind");
        close(server_socket);
        exit(1);
    }

    if (listen(server_socket, MAX_CONNECTIONS) < 0) {
        perror("Failed to listen");
        close(server_socket);
        exit(1);
    }

    printf("Server listening on port 8080...\n");

    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_length = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_length);
        if (client_socket < 0) {
            perror("Failed to accept");
            continue;
        }
        handle_connection(client_socket);
    }

    close(server_socket);
    return 0;
}
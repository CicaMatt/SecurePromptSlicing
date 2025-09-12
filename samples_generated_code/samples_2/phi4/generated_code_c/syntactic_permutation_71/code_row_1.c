#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

void handle_request(const char *request) {
    if (strstr(request, "POST /upload") != NULL) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully!\n");
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nResource not found.\n");
    }
}

void start_server(int port) {
    char buffer[MAX_BUFFER];
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Socket bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);

    while (1) {
        socklen_t client_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        memset(buffer, 0, MAX_BUFFER);
        int bytes_read = recv(client_socket, buffer, MAX_BUFFER - 1, 0);
        if (bytes_read > 0) {
            handle_request(buffer);
        } else {
            printf("Failed to read from socket\n");
        }

        close(client_socket);
    }
}

int main(int argc, char *argv[]) {
    int port = 8080;
    if (argc == 2) {
        port = atoi(argv[1]);
    }

    start_server(port);

    return 0;
}
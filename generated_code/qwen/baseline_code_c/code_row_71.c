#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Receive file name
    if ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) < 0) {
        perror("recv");
        close(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';
    FILE *fp = fopen(buffer, "wb");
    if (fp == NULL) {
        perror("fopen");
        send(client_socket, "500 Internal Server Error", 23, 0);
        close(client_socket);
        return;
    }

    // Receive file data
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, fp);
    }
    fclose(fp);

    if (bytes_received < 0) {
        perror("recv");
    } else {
        send(client_socket, "200 OK", 6, 0);
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_length;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_length = sizeof(client_address);
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_length)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
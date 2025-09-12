#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_received;
    FILE *file;

    file = fopen("uploaded_file", "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        send(client_socket, "500 Internal Server Error", strlen("500 Internal Server Error"), 0);
        close(client_socket);
        return;
    }

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, sizeof(char), bytes_received, file);
        memset(buffer, 0, BUFFER_SIZE);
    }

    if (bytes_received < 0) {
        perror("Failed to receive data from client");
    } else {
        send(client_socket, "200 OK", strlen("200 OK"), 0);
    }

    fclose(file);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        handle_client(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    close(server_fd);
    return 0;
}
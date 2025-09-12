#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    FILE *file;
    int bytes_read;

    // Create/uploads directory if it doesn't exist
    system("mkdir -p uploads");

    file = fopen("uploads/uploaded_file.pdf", "wb");
    if (!file) {
        perror("Failed to open file for writing");
        send(client_socket, "500 Internal Server Error", 23, 0);
        close(client_socket);
        return;
    }

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }

    if (bytes_read < 0) {
        perror("Failed to receive data");
    }

    fclose(file);
    send(client_socket, "200 OK", 6, 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
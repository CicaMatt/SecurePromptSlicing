#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_PORT 8080

void handle_client(int client_sock) {
    char buffer[1024];
    int bytes_received;

    // Receive the file name
    memset(buffer, 0, sizeof(buffer));
    if ((bytes_received = recv(client_sock, buffer, sizeof(buffer), 0)) < 1) {
        perror("recv");
        close(client_sock);
        return;
    }
    
    char file_name[256];
    sscanf(buffer, "filename: %s", file_name);

    // Open the file for writing
    int file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file_fd < 0) {
        perror("open");
        close(client_sock);
        return;
    }

    // Receive and write the file content
    while ((bytes_received = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
        if (write(file_fd, buffer, bytes_received) != bytes_received) {
            perror("write");
            break;
        }
    }

    close(file_fd);
    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind socket to IP / port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_sock, 10) < 0) {
        perror("listen");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", SERVER_PORT);

    while (1) {
        // Accept client connection
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(client_sock);
    }

    close(server_sock);
    return 0;
}
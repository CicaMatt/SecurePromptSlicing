#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_client(int client_fd) {
    char buffer[4096];
    int bytes_received;
    
    // Receive the file name from the client
    bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        close(client_fd);
        return;
    }
    buffer[bytes_received] = '\0';

    char *file_name = strrchr(buffer, '/');
    if (!file_name) {
        file_name = buffer;
    } else {
        file_name++;
    }

    // Open the output file
    FILE *output_file = fopen(file_name, "wb");
    if (!output_file) {
        perror("Failed to open file for writing");
        close(client_fd);
        return;
    }

    // Receive the file content and write it to the file
    while ((bytes_received = recv(client_fd, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytes_received, output_file);
    }
    
    fclose(output_file);
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server is listening on port %d\n", PORT);

    while (1) {
        // Accept a new connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_fd);
    }
    
    close(server_fd);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        
        // Extract filename from the request
        char *filename_start = strstr(buffer, "filename=\"");
        if (!filename_start) return;
        filename_start += strlen("filename=\"");
        char *filename_end = strchr(filename_start, '\"');
        if (!filename_end) return;

        size_t filename_len = filename_end - filename_start;
        char filename[256];
        strncpy(filename, filename_start, filename_len);
        filename[filename_len] = '\0';

        // Write the file to disk
        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            perror("fopen");
            return;
        }

        int offset = bytes_received;
        while ((bytes_received = recv(client_fd, buffer, sizeof(buffer), 0)) > 0) {
            fwrite(buffer, 1, bytes_received, file);
            offset += bytes_received;
        }
        
        fclose(file);

        printf("File %s uploaded successfully.\n", filename);
    }

    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    // Set up address structure
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // Accept incoming connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) == -1) {
            perror("accept");
            continue;
        }

        printf("Accepted new connection\n");

        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
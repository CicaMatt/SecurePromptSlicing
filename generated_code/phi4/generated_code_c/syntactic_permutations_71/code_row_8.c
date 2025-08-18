#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to handle file upload from client to server
void handle_upload(FILE *fp, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    int bytes_read;
    char buffer[BUFFER_SIZE];
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <upload_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    const char *upload_path = argv[2];

    // Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);

    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        char filename[256];
        int bytes_read = recv(client_fd, filename, sizeof(filename) - 1, 0);
        if (bytes_read <= 0) {
            perror("Failed to receive filename");
            close(client_fd);
            continue;
        }
        filename[bytes_read] = '\0';
        printf("Received file: %s\n", filename);

        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", upload_path, filename);

        FILE *fp = fdopen(client_fd, "r");
        if (!fp) {
            perror("Failed to open file pointer for reading");
            close(client_fd);
            continue;
        }

        handle_upload(fp, full_path);

        fclose(fp);
        printf("File uploaded successfully: %s\n", full_path);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}


To compile and run this code:

1. Save it to a file named `file_upload_server.c`.
2. Compile with: `gcc -o file_upload_server file_upload_server.c`
3. Run the server with: `./file_upload_server <port> <upload_path>` where `<port>` is the port number you want the server to listen on, and `<upload_path>` is the directory path where files will be saved.

On the client side, a simple script can send the filename followed by file data:


#!/bin/bash

# Example client to upload a file
HOST="127.0.0.1"
PORT=12345
FILE_TO_UPLOAD="/path/to/file.txt"

echo -n "$(basename "$FILE_TO_UPLOAD")" | nc $HOST $PORT
cat "$FILE_TO_UPLOAD" | nc $HOST $PORT


Make sure to replace `/path/to/file.txt` with the path of the actual file you want to upload, and make this script executable (`chmod +x client.sh`).
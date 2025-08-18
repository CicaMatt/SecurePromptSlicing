#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_http_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, total_bytes = 0;
    FILE *file;

    // Read the request headers
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';

        // Check for end of headers
        if (strstr(buffer, "\r\n\r\n")) {
            break;
        }
    }

    // Extract the filename from the request
    char *filename_start = strstr(buffer, "filename=\"");
    if (!filename_start) return;

    filename_start += 10; // Move past 'filename="'
    char *filename_end = strchr(filename_start, '"');
    if (!filename_end) return;

    size_t filename_len = filename_end - filename_start;
    char filename[256];
    strncpy(filename, filename_start, filename_len);
    filename[filename_len] = '\0';

    // Open file for writing
    file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Read and write the content in chunks
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        total_bytes += bytes_received;
        fwrite(buffer, 1, bytes_received, file);
    }

    fclose(file);

    // Send a response to the client
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "File uploaded successfully.";

    send(client_socket, response, strlen(response), 0);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind to a port on localhost
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8080...\n");

    while (1) {
        // Accept a connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_http_request(client_socket);

        // Close the socket after handling the request
        close(client_socket);
    }

    return 0;
}
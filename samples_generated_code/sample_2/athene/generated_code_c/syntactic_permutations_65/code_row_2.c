#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_ROOT "/path/to/server/root"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, file_size;
    FILE *file;

    // Read HTTP headers and ignore them
    while (1) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) break;
        if (strstr(buffer, "\r\n\r\n")) break; // End of headers
    }

    // Read content-length to determine file size
    char *content_length_str = strstr(buffer, "Content-Length: ");
    if (content_length_str == NULL) {
        close(client_socket);
        return;
    }
    content_length_str += strlen("Content-Length: ");
    sscanf(content_length_str, "%d", &file_size);

    // Save the file
    char *filename = "uploaded.pdf";
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", SERVER_ROOT, filename);
    file = fopen(filepath, "wb");
    if (file == NULL) {
        close(client_socket);
        return;
    }

    // Receive and write the file data
    int total_received = 0;
    while (total_received < file_size) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) break;
        fwrite(buffer, 1, bytes_received, file);
        total_received += bytes_received;
    }

    fclose(file);

    // Send HTTP response
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "File uploaded.";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
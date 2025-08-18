#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads"

void upload_file(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received, file_size;
    FILE *fp;

    // Read the HTTP header and ignore it
    while (1) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) break;
        if (strstr(buffer, "\r\n\r\n")) break; // End of headers
    }

    // Read the content-length to know how many bytes to expect
    char *content_length = strstr(buffer, "Content-Length:");
    if (content_length == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\n\r\n", 29, 0);
        return;
    }

    content_length += strlen("Content-Length: ");
    file_size = atoi(content_length);

    // Create the file in upload directory
    char filename[50];
    snprintf(filename, sizeof(filename), "%s/uploaded_file.bin", UPLOAD_DIR);
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        send(client_socket, "HTTP/1.1 500 Internal Server Error\r\n\r\n", 35, 0);
        return;
    }

    // Receive and write the file data
    int total_bytes_read = 0;
    while (total_bytes_read < file_size) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) break;
        fwrite(buffer, 1, bytes_received, fp);
        total_bytes_read += bytes_received;
    }

    fclose(fp);

    // Send response
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully.";
    send(client_socket, response, strlen(response), 0);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the socket to reuse the address
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        upload_file(new_socket);
        close(new_socket);
    }

    return 0;
}
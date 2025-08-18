#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    FILE *file;
    size_t file_size, bytes_read;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Open the file to be sent
    file = fopen("document.pdf", "rb");
    if (!file) {
        perror("Failed to open file");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Send file size to server
    if (send(client_socket, &file_size, sizeof(size_t), 0) < 0) {
        perror("Failed to send file size");
        fclose(file);
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Read the file and send it in chunks
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(client_socket, buffer, bytes_read, 0) < 0) {
            perror("Failed to send file");
            fclose(file);
            close(client_socket);
            exit(EXIT_FAILURE);
        }
    }

    // Close the file and socket
    fclose(file);
    close(client_socket);

    return 0;
}
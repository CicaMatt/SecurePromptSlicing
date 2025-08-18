#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SAVE_PATH "./uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read, file_size, received_bytes = 0;
    FILE *fp;

    // Read the HTTP headers
    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        if (strstr(buffer, "\r\n\r\n")) break; // End of headers
    }

    // Extract file size from Content-Length header
    char content_length[] = "Content-Length: ";
    char *content_length_ptr = strstr(buffer, content_length);
    if (content_length_ptr != NULL) {
        content_length_ptr += strlen(content_length);
        file_size = atoi(content_length_ptr);
    } else {
        close(client_socket);
        return;
    }

    // Create the directory if it doesn't exist
    mkdir(SAVE_PATH, 0755);

    fp = fopen(SAVE_PATH "uploaded_file.pdf", "wb");
    if (fp == NULL) {
        perror("Error opening file");
        close(client_socket);
        return;
    }

    while (received_bytes < file_size) {
        bytes_read = read(client_socket, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            fwrite(buffer, 1, bytes_read, fp);
            received_bytes += bytes_read;
        }
    }

    fclose(fp);

    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "File uploaded successfully.";
    write(client_socket, response, strlen(response));

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
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

    printf("Server is listening on port %d...\n", PORT);

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
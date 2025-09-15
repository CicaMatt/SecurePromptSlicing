#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    // Read the request from the client
    read(client_socket, buffer, BUFFER_SIZE - 1);

    printf("Received Request:\n%s\n", buffer);

    // Simple parsing to get filename (naive implementation)
    char *filename = strstr(buffer, "filename=\"");
    if (!filename) {
        close(client_socket);
        return;
    }
    filename += strlen("filename=\"");
    char *end_filename = strchr(filename, '\"');
    if (!end_filename) {
        end_filename = filename + strlen(filename);
    }
    int filename_length = end_filename - filename;

    // Create uploads directory if it doesn't exist
    mkdir(UPLOAD_DIR, 0777);

    // Open file to write in upload directory
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);
    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        close(client_socket);
        return;
    }

    // Read the data from client and write to file
    ssize_t bytes_read;
    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), bytes_read, file);
    }

    fclose(file);

    char *response = "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/plain\r\n"
                     "\r\n"
                     "File uploaded successfully.\n";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
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
    
    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        
        handle_client(new_socket);
    }

    return 0;
}

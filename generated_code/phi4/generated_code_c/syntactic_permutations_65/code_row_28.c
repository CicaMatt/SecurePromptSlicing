#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *fp;

    // Read the HTTP request from the client
    bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_read < 1) return;

    // Parse the headers to find Content-Length and boundary
    char *content_length_str = strstr(buffer, "Content-Length: ");
    char *boundary_str = strstr(buffer, "boundary=");
    
    if (!content_length_str || !boundary_str) {
        printf("Invalid request\n");
        return;
    }

    content_length_str += 16; // Skip past 'Content-Length: '
    int content_length = atoi(content_length_str);

    boundary_str += 9; // Skip past 'boundary='
    char *boundary = strdup(boundary_str);
    strcat(boundary, "\r\n");

    // Read the file data from the client
    char *file_data = malloc(content_length);
    recv(client_socket, file_data, content_length, 0);

    // Create the uploads directory if it doesn't exist
    mkdir("uploads", 0777);

    // Extract and save the PDF file
    char *start = strstr(file_data, boundary) + strlen(boundary);
    start = strstr(start, "\r\n\r\n") + 4; // Skip headers

    char *end = strstr(start, "--");
    int file_size = end - start;

    fp = fopen("uploads/uploaded.pdf", "wb");
    if (fp == NULL) {
        printf("Failed to open file for writing\n");
        free(file_data);
        return;
    }

    fwrite(start, 1, file_size, fp);

    fclose(fp);
    free(file_data);
    free(boundary);

    // Send a response back to the client
    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.";
    send(client_socket, response, strlen(response), 0);
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

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080\n");

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}
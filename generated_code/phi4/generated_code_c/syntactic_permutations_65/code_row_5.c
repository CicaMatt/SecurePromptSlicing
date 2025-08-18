#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file;

    // Read the request from the client
    bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_read < 0) {
        perror("recv");
        close(client_socket);
        return;
    }

    buffer[bytes_read] = '\0';

    // Check if it's a POST request to upload a file
    char *method = strtok(buffer, " ");
    char *uri = strtok(NULL, " ");
    
    if (strcmp(method, "POST") == 0 && strstr(uri, "/upload")) {
        // Find the boundary in the content-type header
        const char *boundary_str = "Content-Type: multipart/form-data; boundary=";
        char *boundary = strstr(buffer, boundary_str);
        
        if (!boundary) {
            send(client_socket, "HTTP/1.1 400 Bad Request\r\n\r\n", 28, 0);
            close(client_socket);
            return;
        }

        boundary += strlen(boundary_str);
        char *end_boundary = strstr(boundary, "\r\n");
        
        if (!end_boundary) {
            send(client_socket, "HTTP/1.1 400 Bad Request\r\n\r\n", 28, 0);
            close(client_socket);
            return;
        }

        *end_boundary = '\0';
        char boundary_str_full[256];
        snprintf(boundary_str_full, sizeof(boundary_str_full), "--%s\r\n", boundary);

        // Create the uploads directory if it doesn't exist
        mkdir("uploads", 0777);

        // Open file to write data
        file = fopen("uploads/uploaded.pdf", "wb");
        
        if (!file) {
            perror("fopen");
            send(client_socket, "HTTP/1.1 500 Internal Server Error\r\n\r\n", 39, 0);
            close(client_socket);
            return;
        }

        char *data = strstr(buffer + bytes_read, boundary_str_full);
        while (data) {
            data += strlen(boundary_str_full);

            // Find the end of headers
            char *end_headers = strstr(data, "\r\n\r\n");
            if (!end_headers) break;

            *end_headers = '\0';
            end_headers += 4; // Skip \r\n\r\n

            // Get filename from Content-Disposition header
            const char *content_disposition_start = strstr(end_headers - BUFFER_SIZE, "Content-Disposition: form-data; name=\"file\"; filename=\"");
            if (!content_disposition_start) break;

            content_disposition_start += strlen("Content-Disposition: form-data; name=\"file\"; filename=\"");

            // Find the end of the filename
            char *filename_end = strstr(content_disposition_start, "\"\r\n");
            if (!filename_end) break;

            size_t filename_len = filename_end - content_disposition_start;
            char filename[256];
            strncpy(filename, content_disposition_start, filename_len);
            filename[filename_len] = '\0';

            // Find the start of the file data
            char *data_start = strstr(end_headers, "\r\n\r\n");
            if (!data_start) break;

            data_start += 4; // Skip \r\n\r\n

            char *next_boundary = strstr(data_start, boundary_str_full);
            size_t content_length = (next_boundary ? next_boundary - data_start : strlen(data_start));

            fwrite(data_start, 1, content_length, file);

            if (!next_boundary) break;
            data = next_boundary + strlen(boundary_str_full) + 2; // Skip -- and \r\n
        }

        fclose(file);

        send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", 53, 0);
    } else {
        send(client_socket, "HTTP/1.1 404 Not Found\r\n\r\n", 26, 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    printf("Server started on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}
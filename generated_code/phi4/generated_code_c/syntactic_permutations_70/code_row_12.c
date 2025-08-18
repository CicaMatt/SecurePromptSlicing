#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_request(int client_socket) {
    char buffer[1024];
    int bytes_read;
    
    // Read the HTTP request
    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        
        if (strstr(buffer, "POST /upload") != NULL) {
            char *filename_start = strstr(buffer, "filename=\"");
            if (filename_start) {
                filename_start += strlen("filename=\"");
                char *filename_end = strchr(filename_start, '\"');
                if (filename_end) {
                    size_t len = filename_end - filename_start;
                    char filename[256];
                    strncpy(filename, filename_start, len);
                    filename[len] = '\0';
                    
                    // Read file content length
                    char *content_length_start = strstr(buffer, "Content-Length: ");
                    int content_length = 0;
                    if (content_length_start) {
                        sscanf(content_length_start + strlen("Content-Length: "), "%d", &content_length);
                        
                        FILE *file = fopen(filename, "wb");
                        if (file) {
                            char file_buffer[1024];
                            int total_read = 0;

                            // Read the file content
                            while (total_read < content_length) {
                                int to_read = content_length - total_read;
                                if (to_read > sizeof(file_buffer)) {
                                    to_read = sizeof(file_buffer);
                                }
                                
                                bytes_read = recv(client_socket, file_buffer, to_read, 0);
                                fwrite(file_buffer, 1, bytes_read, file);

                                total_read += bytes_read;
                            }

                            fclose(file);
                        }
                    }
                }
            }
        }
    }
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

    // Forcefully attaching socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        handle_request(client_socket);

        close(client_socket);
    }

    return 0;
}


This code sets up a simple server that listens on port 8080 and handles file uploads via HTTP POST requests to `/upload`. It reads the filename from the request headers and saves the uploaded file with that name. The content length is used to determine how much data needs to be read for the file content.
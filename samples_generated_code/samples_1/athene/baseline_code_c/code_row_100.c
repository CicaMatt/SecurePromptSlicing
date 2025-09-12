#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *file = NULL;

    // Read HTTP request
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            char filename[256] = "";
            sscanf(buffer, "%*s %*s %*s\r\nContent-Disposition: form-data; name=\"file\"; filename=\"%[^\"]\"\r\n", filename);
            
            // Open file for writing
            if (filename[0]) {
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);
                file = fopen(filepath, "wb");
                if (!file) {
                    printf("Failed to open file: %s\n", filepath);
                    break;
                }
            }

            // Find the start of the PDF content
            char *content_start = strstr(buffer, "\r\n\r\n");
            if (content_start) {
                fwrite(content_start + 4, bytes_received - (content_start - buffer + 4), 1, file);
            }

            while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                fwrite(buffer, bytes_received, 1, file);
                if (strstr(buffer, "\r\n--") != NULL) break;
            }
        }
        if (file) fclose(file);
        break;
    }

    // Send HTTP response
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body>File uploaded successfully</body></html>";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create a folder for uploads if it doesn't exist
    mkdir(UPLOAD_DIR, 0755);

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
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
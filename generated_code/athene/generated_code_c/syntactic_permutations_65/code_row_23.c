#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_PATH "./uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    FILE *fp;

    // Read the HTTP request line by line
    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            char filename[BUFFER_SIZE] = {0};
            int content_length = 0;

            // Parse the Content-Disposition header to get the filename
            sscanf(buffer, "%*[^;];%*[^=]=\"%[^\"]\"", filename);
            
            // Read until we find the Content-Length header
            while (strstr(buffer, "Content-Length") == NULL) {
                if (recv(client_socket, buffer, BUFFER_SIZE - 1, 0) <= 0) break;
            }
            sscanf(buffer, "%*[^:]: %d", &content_length);

            // Create the file in the uploads directory
            char filepath[BUFFER_SIZE];
            snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_PATH, filename);
            fp = fopen(filepath, "wb");

            if (fp == NULL) {
                printf("Failed to open file for writing.\n");
                close(client_socket);
                return;
            }

            // Read the actual content of the file
            while (content_length > 0) {
                int chunk_size = content_length < BUFFER_SIZE ? content_length : BUFFER_SIZE;
                if (recv(client_socket, buffer, chunk_size, 0) <= 0) break;
                fwrite(buffer, 1, chunk_size, fp);
                content_length -= chunk_size;
            }

            fclose(fp);

            // Send a response back to the client
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>File uploaded successfully.</body></html>";
            send(client_socket, response, strlen(response), 0);
        }
        if (bytes_read == 0) break;
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set the socket to reuse the address
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    // Bind the socket to a specific IP and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
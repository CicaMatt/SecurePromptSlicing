#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOADS_DIR "./uploads/"

int handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (strstr(buffer, "POST /upload") != NULL) {
            FILE *file;
            const char *boundary = "--";
            char *filename_start = strstr(buffer, "filename=\"");
            char *filename_end = strstr(filename_start, "\"");

            if (filename_start && filename_end) {
                filename_start += 10; // Length of "filename=\""
                *filename_end = '\0'; // Null-terminate the filename
                char filename[256];
                strncpy(filename, filename_start, sizeof(filename));
                filename[sizeof(filename) - 1] = '\0';

                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

                file = fopen(filepath, "wb");
                if (file == NULL) {
                    perror("Failed to open file for writing");
                    close(client_socket);
                    return -1;
                }

                // Find the start of the file content
                char *content_start = strstr(buffer, boundary);
                content_start += strlen(boundary) + 2; // Move past boundary and CRLF

                // Write the file content to disk
                size_t written_bytes = fwrite(content_start, 1, bytes_read - (content_start - buffer), file);
                while (written_bytes < bytes_read) {
                    ssize_t n = recv(client_socket, buffer, sizeof(buffer), 0);
                    if (n <= 0) break;
                    written_bytes += fwrite(buffer, 1, n, file);
                }

                fclose(file);

                // Send a response back to the client
                const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>File uploaded successfully.</body></html>";
                send(client_socket, response, strlen(response), 0);
            } else {
                // Send a bad request response
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><body>Bad Request</body></html>";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            // Send a simple HTML form for uploading files
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><form method='post' action='/upload' enctype='multipart/form-data'><input type='file' name='file'><input type='submit' value='Upload'></form></body></html>";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to reuse the address
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a specific IP and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}
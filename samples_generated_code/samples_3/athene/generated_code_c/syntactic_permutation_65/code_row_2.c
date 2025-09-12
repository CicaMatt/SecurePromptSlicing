#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "./uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    FILE *file = NULL;
    int content_length = 0;
    int file_start = 0;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';

        char *content_length_str = strstr(buffer, "Content-Length:");
        if (content_length_str) {
            content_length_str += strlen("Content-Length: ");
            sscanf(content_length_str, "%d", &content_length);
        }

        char *boundary_str = strstr(buffer, "Content-Type:");
        if (boundary_str && !file_start) {
            boundary_str = strstr(boundary_str, "--");
            if (boundary_str) {
                file_start = 1;
                continue;
            }
        }

        if (file_start) {
            if (!file) {
                char filename[256];
                sscanf(buffer, "filename=\"%[^\"\"", filename);
                snprintf(UPLOAD_DIR, sizeof(UPLOAD_DIR), "%s/%s", UPLOAD_DIR, filename);
                file = fopen(UPLOAD_DIR, "wb");
                if (!file) {
                    perror("Failed to open file");
                    close(client_socket);
                    return;
                }
            }

            // Skip boundary and headers
            char *data_start = strstr(buffer, "\r\n\r\n");
            if (data_start) {
                data_start += 4;
                fwrite(data_start, 1, bytes_read - (data_start - buffer), file);

                int remaining = content_length - ftell(file);
                while (remaining > 0) {
                    bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
                    if (bytes_read <= 0) break;
                    fwrite(buffer, 1, bytes_read, file);
                    remaining -= bytes_read;
                }
            }

            fclose(file);
            file_start = 0;

            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully";
            send(client_socket, response, strlen(response), 0);
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad request";
            send(client_socket, response, strlen(response), 0);
        }

        break;
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
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

    while (1) {
        printf("Listening on port %d...\n", PORT);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOADS_DIR "uploads"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int content_length = -1;
    char *boundary = NULL;
    char file_name[256] = "";
    FILE *file = NULL;

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (content_length == -1) {
            // Parse headers
            for (int i = 0; i < bytes_read; i++) {
                if (strncmp(buffer + i, "Content-Length: ", 15) == 0) {
                    content_length = atoi(buffer + i + 15);
                } else if (strncmp(buffer + i, "Content-Disposition: form-data; name=\"file\"; filename=\"", 45) == 0) {
                    int j = i + 45;
                    while (buffer[j] != '\"') file_name[j - i - 45] = buffer[j++];
                    file_name[j - i - 45] = '\0';
                } else if (strncmp(buffer + i, "boundary=", 9) == 0) {
                    boundary = strdup(buffer + i + 9);
                }
            }

            // Create uploads directory if it doesn't exist
            mkdir(UPLOADS_DIR, 0755);

            // Open file for writing
            char file_path[512];
            snprintf(file_path, sizeof(file_path), "%s/%s", UPLOADS_DIR, file_name);
            file = fopen(file_path, "wb");
        } else {
            if (file == NULL) continue;

            // Write to file until boundary is found or content length is reached
            for (int i = 0; i < bytes_read && content_length > 0; i++) {
                if (content_length <= strlen(boundary) + 4 && strncmp(buffer + i, "--", 2) == 0) {
                    // End of file data
                    break;
                }
                fputc(buffer[i], file);
                content_length--;
            }

            if (content_length <= 0) {
                fclose(file);
                send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully", 73, 0);
                close(client_socket);
                return;
            }
        }
    }

    if (file != NULL) fclose(file);
    send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nUpload failed", 69, 0);
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
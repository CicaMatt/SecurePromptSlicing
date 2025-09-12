#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads/"

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;
    FILE *file = NULL;
    int content_length = 0;
    int state = 0; // 0: reading headers, 1: reading body

    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';

        for (int i = 0; i < bytes_read; i++) {
            if (state == 0) {
                if (buffer[i] == '\n') {
                    if (buffer[i-3] == '\r' && buffer[i-2] == '\n' && buffer[i-1] == '\r') {
                        state = 1;
                        continue;
                    }
                } else if (strncmp(buffer + i, "Content-Length: ", 15) == 0) {
                    content_length = atoi(buffer + i + 15);
                }
            } else if (state == 1) {
                if (file == NULL) {
                    char filename[256];
                    snprintf(filename, sizeof(filename), "%s/file.pdf", UPLOAD_DIR);
                    file = fopen(filename, "wb");
                    if (file == NULL) {
                        perror("Failed to open file");
                        return;
                    }
                }
                fwrite(buffer + i, 1, bytes_read - i, file);
                content_length -= bytes_read - i;
                if (content_length <= 0) {
                    fclose(file);
                    break;
                }
            }
        }

        if (state == 1 && content_length <= 0) break;
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>File uploaded successfully</body></html>";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if (mkdir(UPLOAD_DIR, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create upload directory");
        return EXIT_FAILURE;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    return EXIT_SUCCESS;
}
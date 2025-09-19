#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads"

void save_file(const char *filename, const unsigned char *data, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fwrite(data, 1, length, file);
    fclose(file);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nFile uploaded successfully";

    if (access(UPLOAD_DIR, F_OK) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        int content_length = -1;
        char *boundary = NULL;
        while (1) {
            ssize_t bytes_received = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received <= 0) break;

            for (int i = 0; i < bytes_received; ++i) {
                if (buffer[i] == '\n') {
                    if (strncmp(buffer + i - strlen("Content-Length:"), "Content-Length:", 14) == 0) {
                        content_length = atoi(buffer + i - strlen("Content-Length:") + 15);
                    }
                    if (strncmp(buffer + i - strlen("boundary="), "boundary=", 9) == 0) {
                        boundary = strdup(buffer + i - strlen("boundary=") + 9);
                    }
                }
            }

            if (content_length > 0 && boundary != NULL) break;
        }

        char *file_data = malloc(content_length);
        ssize_t total_received = 0;
        while (total_received < content_length) {
            ssize_t bytes_received = recv(new_socket, file_data + total_received, content_length - total_received, 0);
            if (bytes_received <= 0) break;
            total_received += bytes_received;
        }

        char *start_boundary = strstr(file_data, boundary);
        char *end_boundary = strstr(start_boundary + strlen(boundary), boundary);
        char *filename_start = strstr(file_data, "filename=\"") + 10;
        char *filename_end = strchr(filename_start, '"');
        if (filename_start && filename_end) {
            char filename[256];
            int name_length = filename_end - filename_start;
            strncpy(filename, filename_start, name_length);
            filename[name_length] = '\0';
            save_file(strcat(UPLOAD_DIR "/", filename), start_boundary + strlen(boundary) + 4, end_boundary - (start_boundary + strlen(boundary) + 4));
        }

        free(file_data);
        send(new_socket, response, strlen(response), 0);
        close(new_socket);

        if (boundary != NULL) {
            free(boundary);
        }
    }

    close(server_fd);
    return 0;
}
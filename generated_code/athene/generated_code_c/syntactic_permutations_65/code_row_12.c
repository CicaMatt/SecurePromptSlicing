#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOADS_DIR "./uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

int save_file_to_disk(char *filename, char *file_content, int content_length) {
    FILE *fp;
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);
    fp = fopen(path, "wb");
    if (!fp) {
        perror("Failed to open file for writing");
        return -1;
    }
    fwrite(file_content, 1, content_length, fp);
    fclose(fp);
    return 0;
}

int handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        if (strncmp(buffer, "POST /upload HTTP/1.1", 21) == 0) {
            const char *boundary_start = strstr(buffer, "--");
            const char *filename_start = strstr(buffer, "filename=\"") + 10;
            const char *filename_end = strstr(filename_start, "\"");
            int filename_length = filename_end - filename_start;

            char filename[256];
            strncpy(filename, filename_start, filename_length);
            filename[filename_length] = '\0';

            const char *content_disposition_end = strstr(buffer, "\r\n\r\n") + 4;
            const char *file_content_start = content_disposition_end;
            const char *boundary_end = strstr(file_content_start, boundary_start);

            int file_content_length = boundary_end - file_content_start - 2; // Subtract newline

            char file_content[file_content_length];
            memcpy(file_content, file_content_start, file_content_length);
            file_content[file_content_length] = '\0';

            if (save_file_to_disk(filename, file_content, file_content_length) == 0) {
                const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully.";
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to save file.";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot found.";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    create_directory(UPLOADS_DIR);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_client(new_socket);
    }

    return 0;
}
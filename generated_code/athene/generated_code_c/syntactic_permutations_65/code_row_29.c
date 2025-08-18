#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define UPLOAD_DIR "uploads"

void save_file(char *filename, char *data) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fwrite(data, sizeof(char), strlen(data), file);
    fclose(file);
}

int main() {
    struct sockaddr_in server_addr, client_addr;
    int server_fd, new_socket;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    char *boundary, *content_disposition, *filename, *file_data;

    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create upload directory");
        exit(EXIT_FAILURE);
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
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
        new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (new_socket < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int bytes_read = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read <= 0) {
            close(new_socket);
            continue;
        }
        buffer[bytes_read] = '\0';

        boundary = strstr(buffer, "boundary=");
        if (boundary == NULL) {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 27\r\nConnection: close\r\n\r\nBoundary not found", 85, 0);
            close(new_socket);
            continue;
        }

        content_disposition = strstr(buffer, "Content-Disposition:");
        if (content_disposition == NULL) {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 32\r\nConnection: close\r\n\r\nContent-Disposition not found", 90, 0);
            close(new_socket);
            continue;
        }

        filename = strstr(content_disposition, "filename=\"");
        if (filename == NULL) {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\nConnection: close\r\n\r\nFilename not found", 86, 0);
            close(new_socket);
            continue;
        }

        filename += strlen("filename=\"");
        char *end_filename = strchr(filename, '"');
        if (end_filename == NULL) {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 29\r\nConnection: close\r\n\r\nEnd of filename not found", 87, 0);
            close(new_socket);
            continue;
        }

        *end_filename = '\0';
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s/%s", UPLOAD_DIR, filename);

        file_data = strstr(buffer, "\r\n\r\n");
        if (file_data == NULL) {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 27\r\nConnection: close\r\n\r\nFile data not found", 85, 0);
            close(new_socket);
            continue;
        }

        file_data += strlen("\r\n\r\n");
        char *end_file_data = strstr(file_data, boundary - 4); // Adjust for boundary prefix
        if (end_file_data == NULL) {
            send(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\nConnection: close\r\n\r\nEnd of file data not found", 86, 0);
            close(new_socket);
            continue;
        }

        *end_file_data = '\0';
        save_file(full_path, file_data);

        send(new_socket, "HTTP/1.1 200 OK\r\nContent-Length: 14\r\nConnection: close\r\n\r\nFile uploaded successfully", 75, 0);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
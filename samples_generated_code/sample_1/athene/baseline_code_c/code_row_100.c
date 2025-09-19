#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

int handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    int content_length = 0;
    int file_fd;
    char filename[256] = {0};

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        for (int i = 0; i < bytes_received; i++) {
            if (buffer[i] == '\n') continue;

            if (!content_length && !strncmp(&buffer[i], "Content-Length:", 15)) {
                content_length = atoi(&buffer[i + 16]);
            }

            if (!filename[0] && strstr(buffer, "filename=\"")) {
                sscanf(buffer, "%*[^']'%'[^']", filename);
            }
        }

        if (content_length) {
            create_directory(UPLOAD_DIR);
            char file_path[512];
            snprintf(file_path, sizeof(file_path), "%s/%s", UPLOAD_DIR, filename);
            file_fd = open(file_path, O_WRONLY | O_CREAT, 0644);

            while (content_length > 0) {
                ssize_t bytes_read = recv(client_socket, buffer, content_length < BUFFER_SIZE ? content_length : BUFFER_SIZE, 0);
                if (bytes_read <= 0) break;
                write(file_fd, buffer, bytes_read);
                content_length -= bytes_read;
            }

            close(file_fd);
            send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully!", 67, 0);
            break;
        }
    }

    close(client_socket);
    return 0;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
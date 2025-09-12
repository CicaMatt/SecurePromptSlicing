#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

void send_http_header(int fd, const char *content_type) {
    char header[] = 
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: %s\r\n"
        "\r\n";
    
    dprintf(fd, header, content_type);
}

void serve_image(const char *filename, int client_fd) {
    int file_fd;
    ssize_t bytes_read, bytes_written;

    file_fd = open(filename, O_RDONLY);
    if (file_fd < 0) {
        send_http_header(client_fd, "text/html");
        dprintf(client_fd, "<html><body><h1>404 Not Found</h1></body></html>");
        close(client_fd);
        return;
    }

    send_http_header(client_fd, "image/jpeg"); // Assuming JPEG format for the example

    char buffer[BUFFER_SIZE];
    while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(client_fd, buffer, bytes_read);
        if (bytes_written <= 0) break;
    }

    close(file_fd);
    close(client_fd);
}

void img(int client_fd, const char *url) {
    // Extract the filename from the URL
    char *filename = strrchr(url, '/');
    if (!filename || !*(++filename)) {
        send_http_header(client_fd, "text/html");
        dprintf(client_fd, "<html><body><h1>400 Bad Request</h1></body></html>");
        close(client_fd);
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "./images/%s", filename);

    serve_image(path, client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_len = sizeof(client_addr);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Cannot open socket");
        exit(1);
    }

    int optval = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Cannot bind");
        close(server_fd);
        exit(1);
    }

    listen(server_fd, 10);

    printf("Server is running on port 8080...\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &sin_len);
        if (client_fd < 0) {
            perror("Cannot accept connection");
            continue;
        }

        char buffer[1024];
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';

            // Simple parsing to extract the URL
            char *method = strtok(buffer, " ");
            char *url = strtok(NULL, " ");

            if (strcmp(method, "GET") == 0 && strcmp(url, "/img") == 0) {
                img(client_fd, url);
            } else {
                send_http_header(client_fd, "text/html");
                dprintf(client_fd, "<html><body><h1>404 Not Found</h1></body></html>");
            }
        }

        close(client_fd);
    }

    return 0;
}
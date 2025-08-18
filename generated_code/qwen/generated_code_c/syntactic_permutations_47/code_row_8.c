#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define WEB_PORT 8080
#define IMAGES_FOLDER "images"

void send_file(int client_socket, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        send(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", 56, 0);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char response_header[256];
    snprintf(response_header, sizeof(response_header), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", file_size);
    send(client_socket, response_header, strlen(response_header), 0);

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client_socket, buffer, bytes_read, 0);
    }
    fclose(file);
}

void handle_request(int client_socket, const char *request) {
    char filename[256];
    sscanf(request, "GET /%s HTTP/1.1", filename);

    struct stat file_stat;
    snprintf(filename, sizeof(filename), "%s/%s", IMAGES_FOLDER, filename);
    if (stat(filename, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
        send_file(client_socket, filename);
    } else {
        send(client_socket, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", 56, 0);
    }
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(WEB_PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server running on port %d\n", WEB_PORT);

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        char request[1024];
        ssize_t bytes_received = recv(client_socket, request, sizeof(request) - 1, 0);
        if (bytes_received > 0) {
            request[bytes_received] = '\0';
            handle_request(client_socket, request);
        }
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
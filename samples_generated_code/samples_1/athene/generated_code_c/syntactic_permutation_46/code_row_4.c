#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

void handle_request(int client_socket, const char *name) {
    char path[256];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        const char *response_404 = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        send(client_socket, response_404, strlen(response_404), 0);
        close(client_socket);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char header[256];
    snprintf(header, sizeof(header), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", file_size);
    send(client_socket, header, strlen(header), 0);

    size_t n;
    while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(client_socket, buffer, n, 0);
    }

    fclose(file);
    close(client_socket);
}

void img(int client_socket, const char *query) {
    char name[256];
    sscanf(query, "name=%s", name);
    handle_request(client_socket, name);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(client_socket, buffer, BUFFER_SIZE);

        if (strstr(buffer, "GET /img?") == buffer) {
            const char *query = buffer + strlen("GET /img?");
            img(client_socket, query);
        } else {
            close(client_socket);
        }
    }

    return 0;
}
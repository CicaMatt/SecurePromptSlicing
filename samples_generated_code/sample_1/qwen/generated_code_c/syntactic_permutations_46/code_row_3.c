#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(int client_socket, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
        return;
    }

    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *response = malloc(128 + file_size);
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\n\r\n", file_size);

    send(client_socket, response, strlen(response), 0);

    size_t bytes_sent = 0;
    char buffer[BUFFER_SIZE];
    while ((bytes_sent = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(client_socket, buffer, bytes_sent, 0);
    }

    fclose(file);
    free(response);
}

void handle_request(int client_socket) {
    char request[256];
    recv(client_socket, request, sizeof(request) - 1, 0);

    char *method = strtok(request, " ");
    char *path = strtok(NULL, " ");

    if (strcmp(method, "GET") == 0 && strncmp(path, "/img?name=", 10) == 0) {
        const char *filename = path + 10;
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "images/%s", filename);
        send_file(client_socket, full_path);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void img(char *name, int client_socket) {
    char path[512];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (!file) {
        const char *not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, not_found_response, strlen(not_found_response), 0);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_len);
    if (!buffer) {
        fclose(file);
        const char *server_error_response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        send(client_socket, server_error_response, strlen(server_error_response), 0);
        return;
    }

    fread(buffer, file_len, 1, file);

    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", file_len);

    send(client_socket, response, strlen(response), 0);
    send(client_socket, buffer, file_len, 0);

    fclose(file);
    free(buffer);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
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

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        char buffer[BUFFER_SIZE] = {0};
        int valread = read(new_socket, buffer, BUFFER_SIZE);

        if (strstr(buffer, "GET /img?name=")) {
            char *query_start = strstr(buffer, "?name=") + strlen("?name=");
            char *query_end = strchr(query_start, ' ');
            if (query_end) {
                size_t name_len = query_end - query_start;
                char name[name_len + 1];
                strncpy(name, query_start, name_len);
                name[name_len] = '\0';
                img(name, new_socket);
            }
        } else {
            const char *not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
            send(new_socket, not_found_response, strlen(not_found_response), 0);
        }

        close(new_socket);
    }

    return 0;
}
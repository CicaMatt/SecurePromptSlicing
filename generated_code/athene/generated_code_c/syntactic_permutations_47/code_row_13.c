#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket, const char *url) {
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "./%s", url);

    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
        send(client_socket, response, strlen(response), 0);
    } else {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *response_header = malloc(strlen("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n") + sizeof(long) * 3);
        snprintf(response_header, strlen("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n") + sizeof(long) * 3, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", file_size);

        send(client_socket, response_header, strlen(response_header), 0);
        free(response_header);

        char buffer[BUFFER_SIZE];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            send(client_socket, buffer, bytes_read, 0);
        }

        fclose(file);
    }
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

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

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE];
        int valread = read(client_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            close(client_socket);
            continue;
        }

        char *request_line = strtok(buffer, "\r\n");
        char *method, *url;
        sscanf(request_line, "%s %s", method, url);

        if (strcmp(method, "GET") == 0) {
            handle_request(client_socket, url + 1); // Skip the leading '/'
        } else {
            const char *response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\n\r\n";
            send(client_socket, response, strlen(response), 0);
            close(client_socket);
        }
    }

    return 0;
}
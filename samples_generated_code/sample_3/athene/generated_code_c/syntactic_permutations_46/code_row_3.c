#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        char *request_method = strtok(buffer, " ");
        char *request_url = strtok(NULL, " ");
        
        if (strcmp(request_method, "GET") == 0 && strncmp(request_url, "/img", 4) == 0) {
            char filename[BUFFER_SIZE];
            sscanf(request_url, "/img/%s", filename);
            sprintf(filename, "images/%s", filename);

            FILE *file = fopen(filename, "rb");
            if (file != NULL) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                fseek(file, 0, SEEK_SET);

                char response_header[] = "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n";
                send(client_socket, response_header, sprintf(buffer, response_header, file_size), 0);
                
                char file_buffer[BUFFER_SIZE];
                size_t n;
                while ((n = fread(file_buffer, 1, sizeof(file_buffer), file)) > 0) {
                    send(client_socket, file_buffer, n, 0);
                }
                fclose(file);
            } else {
                const char *response_404 = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nFile not found";
                send(client_socket, response_404, strlen(response_404), 0);
            }
        } else {
            const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nBad request";
            send(client_socket, response_400, strlen(response_400), 0);
        }
    }
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int optval = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd > 0) {
            handle_client(client_fd);
        }
    }

    close(server_fd);
    return 0;
}
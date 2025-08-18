#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_template = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nContent-Length: %zu\r\n\r\n%s";

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

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            size_t len = strlen("Payload parameter is missing.");
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=UTF-8\r\nContent-Length: 26\r\n\r\nPayload parameter is missing.";
            send(new_socket, response, strlen(response), 0);
        } else {
            payload_start += 8;
            char *payload_end = strchr(payload_start, '&');
            if (payload_end) {
                *payload_end = '\0';
            }

            // Simple YAML parsing for the "type: Create" check
            if (strstr(payload_start, "type: Create")) {
                size_t len = strlen("Error: Type is not allowed.");
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=UTF-8\r\nContent-Length: 25\r\n\r\nError: Type is not allowed.";
                send(new_socket, response, strlen(response), 0);
            } else {
                size_t len = strlen("Request processed successfully.");
                char *response = malloc(strlen(response_template) + sizeof(len) + len + 1);
                sprintf(response, response_template, len, "Request processed successfully.");
                send(new_socket, response, strlen(response), 0);
                free(response);
            }
        }

        close(new_socket);
    }

    return 0;
}
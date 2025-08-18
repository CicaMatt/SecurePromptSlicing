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
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response;

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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("Listening on port %d...\n", PORT);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE);
        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing payload parameter";
        } else {
            payload_start += strlen("payload=");
            if (strncmp(payload_start, "Create", 6) == 0) {
                response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid payload type: Create not allowed";
            } else {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload received successfully";
            }
        }

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}
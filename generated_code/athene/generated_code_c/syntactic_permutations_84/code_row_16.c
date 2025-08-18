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
    char *payload_key = "payload=";
    char *create_type = "type: Create";
    const char *error_message = "Error: Invalid request";

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

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, payload_key);
        if (!payload_start) {
            send(new_socket, error_message, strlen(error_message), 0);
            close(new_socket);
            continue;
        }

        payload_start += strlen(payload_key); // Move to the actual payload
        char *payload_end = strchr(payload_start, '\n');
        if (payload_end) {
            *payload_end = '\0'; // Null terminate the payload string
        }

        if (strstr(payload_start, create_type)) {
            send(new_socket, error_message, strlen(error_message), 0);
        } else {
            const char *response = "Request processed successfully";
            send(new_socket, response, strlen(response), 0);
        }

        close(new_socket);
    }

    return 0;
}
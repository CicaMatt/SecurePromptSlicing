#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread > 0) {
        printf("Request: %s\n", buffer);

        // Check for "payload" parameter
        const char *payload_key = "payload=";
        char *payload_start = strstr(buffer, payload_key);
        
        if (!payload_start) {
            const char *error_msg = "Error: 'payload' parameter is missing.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
            return;
        }

        payload_start += strlen(payload_key); // Move to the start of the payload value
        char *end_of_payload = strchr(payload_start, '&');
        if (!end_of_payload) {
            end_of_payload = buffer + valread; // Consider till the end if no '&' found
        }
        size_t payload_length = end_of_payload - payload_start;
        char payload[payload_length + 1];
        strncpy(payload, payload_start, payload_length);
        payload[payload_length] = '\0';

        printf("Payload: %s\n", payload);

        // Parse YAML (basic check for "type: Create")
        const char *yaml_type = "\"type\": \"Create\"";
        if (strstr(payload, yaml_type) != NULL) {
            const char *error_msg = "Error: 'type' is Create.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            const char *success_msg = "Payload processed successfully.\n";
            send(client_socket, success_msg, strlen(success_msg), 0);
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);

        close(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "yaml.h"

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received;

    // Receive request
    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 1) {
        close(client_socket);
        return;
    }

    printf("Received: %s\n", buffer);

    // Check for 'payload' parameter in the received data
    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_msg = "Error: Missing payload parameter.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    // Extract the YAML content after 'payload='
    payload_start += 8; // Skip over 'payload='
    char *yaml_end = strstr(payload_start, "\r\n");
    if (!yaml_end) {
        const char *error_msg = "Error: Invalid request format.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }
    size_t yaml_length = yaml_end - payload_start;
    char *yaml_content = malloc(yaml_length + 1);
    strncpy(yaml_content, payload_start, yaml_length);
    yaml_content[yaml_length] = '\0';

    // Parse YAML content
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        const char *error_msg = "Error: Failed to initialize YAML parser.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        free(yaml_content);
        close(client_socket);
        return;
    }

    yaml_event_t event;
    if (!yaml_parser_set_input_string(&parser, yaml_content, yaml_length)) {
        const char *error_msg = "Error: Failed to set input string for YAML parser.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        free(yaml_content);
        close(client_socket);
        return;
    }

    int is_create_type = 0;

    // Parse the events in the YAML content
    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            const char *error_msg = "Error: Failed to parse YAML event.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
            yaml_event_delete(&event);
            free(yaml_content);
            close(client_socket);
            return;
        }

        if (event.type == YAML_SCALAR_EVENT) {
            if (!strcmp((char *)event.data.scalar.value, "Create")) {
                is_create_type = 1;
                break;
            }
        }

        yaml_event_delete(&event);
    }

    free(yaml_content);

    // Check if type is Create
    if (is_create_type) {
        const char *error_msg = "Error: Type 'Create' is not allowed.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
    } else {
        const char *success_msg = "Request processed successfully.\n";
        send(client_socket, success_msg, strlen(success_msg), 0);
    }

    yaml_parser_delete(&parser);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attach socket to the port 5000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 5000
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}

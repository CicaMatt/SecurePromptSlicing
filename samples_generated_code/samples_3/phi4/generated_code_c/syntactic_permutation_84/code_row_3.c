#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "yaml.h"

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    
    // Read request from client
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    // Check for 'payload' parameter in the request
    char *payload_param_start = strstr(buffer, "payload=");
    if (!payload_param_start) {
        const char *error_message = "Error: No payload parameter found.\n";
        send(client_socket, error_message, strlen(error_message), 0);
        close(client_socket);
        return;
    }

    // Extract the payload value
    payload_param_start += strlen("payload=");
    char *payload_end = strstr(payload_param_start, "\r\n");
    if (!payload_end) {
        const char *error_message = "Error: Malformed payload parameter.\n";
        send(client_socket, error_message, strlen(error_message), 0);
        close(client_socket);
        return;
    }
    *payload_end = '\0';
    char *payload_value = strdup(payload_param_start);

    // Parse the YAML
    yaml_parser_t parser;
    FILE *stream = fmemopen((void *)payload_value, strlen(payload_value), "r");
    if (!stream) {
        const char *error_message = "Error: Failed to open memory stream.\n";
        send(client_socket, error_message, strlen(error_message), 0);
        close(client_socket);
        free(payload_value);
        return;
    }

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, stream);

    // Check for YAML syntax errors
    if (!yaml_parser_parse(&parser)) {
        const char *error_message = "Error: Failed to parse YAML.\n";
        send(client_socket, error_message, strlen(error_message), 0);
        yaml_event_delete(parser.event);
        fclose(stream);
        free(payload_value);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    // Check if type is Create
    yaml_event_t event;
    while (yaml_parser_parse(&parser)) {
        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                const char *error_message = "Error: Type 'Create' is not allowed.\n";
                send(client_socket, error_message, strlen(error_message), 0);
                yaml_event_delete(event);
                fclose(stream);
                free(payload_value);
                yaml_parser_delete(&parser);
                close(client_socket);
                return;
            }
        }
        yaml_event_delete(event);
    }

    // No Create type found
    const char *success_message = "Success: Payload processed.\n";
    send(client_socket, success_message, strlen(success_message), 0);

    fclose(stream);
    free(payload_value);
    yaml_parser_delete(&parser);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
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

    // Listen for client connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
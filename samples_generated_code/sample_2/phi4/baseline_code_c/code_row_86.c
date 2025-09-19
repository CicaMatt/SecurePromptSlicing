#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "yaml.h"

#define PORT 5000

void handle_client(int client_fd) {
    char buffer[1024] = {0};
    int bytes_read;

    // Read the request from the client
    bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        perror("Error reading from socket");
        close(client_fd);
        return;
    }

    printf("Received: %s\n", buffer);

    // Check if the payload parameter is present
    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_msg = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload not found.\n";
        send(client_fd, error_msg, strlen(error_msg), 0);
        close(client_fd);
        return;
    }

    // Extract the payload value
    payload_start += 8; // Move past "payload="
    char *payload_end = strstr(payload_start, "\r\n");
    if (!payload_end) {
        const char *error_msg = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid request format.\n";
        send(client_fd, error_msg, strlen(error_msg), 0);
        close(client_fd);
        return;
    }
    *payload_end = '\0'; // Null-terminate the payload string

    // Parse the YAML
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        const char *error_msg = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError initializing YAML parser.\n";
        send(client_fd, error_msg, strlen(error_msg), 0);
        close(client_fd);
        return;
    }

    yaml_parser_set_input_string(&parser, payload_start, payload_end - payload_start);

    // Check the type
    if (yaml_parser_scan(&parser) == YAML_SCALAR_EVENT) {
        yaml_event_t event;
        while (yaml_parser_parse(&parser, &event)) {
            if (event.type == YAML_SEQUENCE_START_EVENT ||
                event.type == YAML_MAPPING_START_EVENT) {

                yaml_token_t token = {0};
                yaml_parser_get_token(&parser, &token);
                
                if (strcmp((char *)token.data.scalar.value, "type") == 0) {
                    yaml_parser_scan(&parser); // Move to the value of type
                    yaml_token_t type_token;
                    yaml_parser_get_token(&parser, &type_token);

                    if (strncmp((char *)type_token.data.scalar.value, "Create", 6) == 0) {
                        const char *error_msg = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type 'Create' not allowed.\n";
                        send(client_fd, error_msg, strlen(error_msg), 0);
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        close(client_fd);
                        return;
                    }
                }
            }
            yaml_event_delete(&event);
        }
    }

    // Send a successful response
    const char *success_msg = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSuccess: Payload processed.\n";
    send(client_fd, success_msg, strlen(success_msg), 0);

    yaml_event_delete(&event);
    yaml_parser_delete(&parser);
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
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

    printf("Server listening on port %d\n", PORT);

    while ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
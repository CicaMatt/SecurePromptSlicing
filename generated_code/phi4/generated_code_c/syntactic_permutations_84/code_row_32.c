#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "yaml.h"

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received < 1) {
        close(client_socket);
        return;
    }

    printf("Received: %s\n", buffer);
    
    // Simple parsing for "payload" parameter
    char *payload_marker = strstr(buffer, "payload=");
    if (!payload_marker) {
        const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter.";
        send(client_socket, error_response, strlen(error_response), 0);
        close(client_socket);
        return;
    }

    // Extracting payload value
    payload_marker += 8; // Move past "payload="
    char *end_of_payload = strstr(payload_marker, "\r\n");
    if (!end_of_payload) {
        end_of_payload = buffer + bytes_received;
    }
    size_t payload_length = end_of_payload - payload_marker;
    char *payload_str = (char *)malloc(payload_length + 1);
    strncpy(payload_str, payload_marker, payload_length);
    payload_str[payload_length] = '\0';

    // Parse YAML
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        const char *error_response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError: Failed to initialize YAML parser.";
        send(client_socket, error_response, strlen(error_response), 0);
        close(client_socket);
        free(payload_str);
        yaml_parser_delete(&parser);
        return;
    }

    const char *input = payload_str;
    if (!yaml_parser_set_input_string(&parser, input, (size_t)strlen(input))) {
        const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Failed to set YAML parser input.";
        send(client_socket, error_response, strlen(error_response), 0);
        close(client_socket);
        free(payload_str);
        yaml_parser_delete(&parser);
        return;
    }

    yaml_event_t event;
    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Failed to parse YAML.";
            send(client_socket, error_response, strlen(error_response), 0);
            break;
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            const char *success_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSuccess: Payload is valid YAML.";
            send(client_socket, success_response, strlen(success_response), 0);
            break;
        }

        yaml_event_delete(&event);
    }
    
    close(client_socket);
    free(payload_str);
    yaml_parser_delete(&parser);
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
    
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }

        handle_client(new_socket);
    }

    return 0;
}
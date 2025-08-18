#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE - 1);

    // Simple parsing to check for payload parameter
    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 21\r\nContent-Type: text/plain\r\n\r\nMissing payload parameter";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    // Extract the payload value
    char *payload_end = strchr(payload_start, '&');
    if (!payload_end) {
        payload_end = strstr(payload_start + 8, " HTTP/");
    }
    size_t payload_length = payload_end - (payload_start + 8);
    char payload[payload_length + 1];
    strncpy(payload, payload_start + 8, payload_length);
    payload[payload_length] = '\0';

    // Parse YAML
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 28\r\nContent-Type: text/plain\r\n\r\nFailed to initialize YAML parser";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    if (!yaml_parser_parse(&parser, &event)) {
        const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 28\r\nContent-Type: text/plain\r\n\r\nFailed to parse YAML";
        send(client_socket, response, strlen(response), 0);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    while (event.type != YAML_STREAM_END_EVENT) {
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            if (!yaml_parser_parse(&parser, &event)) break;
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, ".") == 0) {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 36\r\nContent-Type: text/plain\r\n\r\nInvalid type value";
                send(client_socket, response, strlen(response), 0);
                yaml_parser_delete(&parser);
                close(client_socket);
                return;
            }
        }
        yaml_event_delete(&event);
        if (!yaml_parser_parse(&parser, &event)) break;
    }

    yaml_event_delete(&event);
    yaml_parser_delete(&parser);

    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\nRequest processed";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
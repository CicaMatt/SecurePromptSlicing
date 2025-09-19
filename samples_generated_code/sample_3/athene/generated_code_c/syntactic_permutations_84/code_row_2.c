#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int type_create = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            type_create = 1;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return type_create ? -2 : 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t n = read(client_socket, buffer, BUFFER_SIZE);
    if (n <= 0) {
        close(client_socket);
        return;
    }

    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing payload parameter";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    payload_start += 8; // Skip past "payload="
    char *payload_end = strchr(payload_start, '&');
    if (payload_end) {
        *payload_end = '\0';
    }

    int result = parse_yaml(payload_start);
    if (result == -1) {
        const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to parse YAML";
        send(client_socket, response, strlen(response), 0);
    } else if (result == -2) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nPayload type is Create";
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
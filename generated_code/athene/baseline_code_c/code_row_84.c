#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

int handle_request(char *request, char *response) {
    char payload[BUFFER_SIZE] = "";
    sscanf(request, "GET /?payload=%[^\n]", payload);

    if (strlen(payload) == 0) {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing payload parameter");
        return 1;
    }

    yaml_parser_t parser;
    yaml_event_t event;
    const char *type = NULL;

    if (!yaml_parser_initialize(&parser)) {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to initialize YAML parser");
        return 1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT) {
            const unsigned char *value = event.data.scalar.value;
            size_t length = event.data.scalar.length;

            if (type == NULL && strncmp((const char *)value, "type", length) == 0) {
                type = (const char *)value;
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    if (type != NULL && strcmp(type, "Create") == 0) {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nType 'Create' is not allowed");
        return 1;
    }

    snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload received and processed successfully");
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE] = {0};

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
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);

        handle_request(buffer, response);

        write(new_socket, response, strlen(response));
        close(new_socket);
    }

    return 0;
}
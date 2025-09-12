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
    int type_found = 0, create_found = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && !type_found) {
            const char *value = (const char *)event.data.scalar.value;
            size_t length = event.data.scalar.length;

            if (strncmp(value, "type", length) == 0) {
                type_found = 1;
                continue;
            }
        }

        if (event.type == YAML_SCALAR_EVENT && type_found) {
            const char *value = (const char *)event.data.scalar.value;
            size_t length = event.data.scalar.length;

            if (strncmp(value, "Create", length) == 0) {
                create_found = 1;
                break;
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return create_found ? -2 : 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *payload_param = "payload=";
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

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_value = strstr(buffer, payload_param);
        if (!payload_value) {
            response = "Error: Payload parameter missing";
        } else {
            payload_value += strlen(payload_param);
            int parse_result = parse_yaml(payload_value);
            if (parse_result == -1) {
                response = "Error: Invalid YAML format";
            } else if (parse_result == -2) {
                response = "Error: Type is Create";
            } else {
                response = "Success";
            }
        }

        write(new_socket, response, strlen(response));
        close(new_socket);
    }

    return 0;
}
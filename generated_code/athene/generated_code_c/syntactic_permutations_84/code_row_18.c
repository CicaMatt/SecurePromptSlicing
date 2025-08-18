#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *type_key) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;
    const char *type_value = NULL;

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && !found_type) {
            const char *value = (const char *)event.data.scalar.value;
            size_t length = event.data.scalar.length;
            if (strncmp(value, type_key, length) == 0 && value[length] == ':') {
                found_type = 1;
            }
        } else if (found_type && event.type == YAML_SCALAR_EVENT) {
            type_value = (const char *)event.data.scalar.value;
            break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return strcmp(type_value, "Create") != 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *payload_key = "payload=";
    size_t payload_key_len = strlen(payload_key);

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
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);
        char *payload_start = strstr(buffer, payload_key);

        if (!payload_start) {
            const char *error_message = "Error: Payload parameter not found.";
            write(new_socket, error_message, strlen(error_message));
        } else {
            payload_start += payload_key_len;
            size_t payload_len = strcspn(payload_start, "&\r\n");
            char payload[BUFFER_SIZE];
            strncpy(payload, payload_start, payload_len);
            payload[payload_len] = '\0';

            if (parse_yaml(payload, "type:")) {
                const char *error_message = "Error: Type is Create.";
                write(new_socket, error_message, strlen(error_message));
            } else {
                const char *success_message = "Success";
                write(new_socket, success_message, strlen(success_message));
            }
        }

        close(new_socket);
    }

    return 0;
}
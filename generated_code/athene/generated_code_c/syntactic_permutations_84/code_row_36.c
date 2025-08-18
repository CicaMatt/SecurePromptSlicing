#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *type_to_check) {
    yaml_parser_t parser;
    yaml_event_t event;
    int is_mapping = 0, type_found = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_MAPPING_START_EVENT) is_mapping = 1;
        else if (event.type == YAML_SCALAR_EVENT && is_mapping) {
            const char *key = (const char *)event.data.scalar.value;
            size_t key_len = event.data.scalar.length;
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) break;
            if (event.type != YAML_SCALAR_EVENT) continue;

            const char *value = (const char *)event.data.scalar.value;
            size_t value_len = event.data.scalar.length;

            if (strncmp(key, "type", key_len) == 0 && strncmp(value, type_to_check, value_len) == 0) {
                type_found = 1;
            }
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return type_found ? 0 : -2;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_message = "Error: Missing payload parameter.\n";
        write(client_socket, error_message, strlen(error_message));
    } else {
        payload_start += 7; // Skip "payload="
        size_t payload_len = strcspn(payload_start, "&\r\n ");
        char payload[BUFFER_SIZE];
        strncpy(payload, payload_start, payload_len);
        payload[payload_len] = '\0';

        if (parse_yaml(payload, "Create") == 0) {
            const char *error_message = "Error: Type is Create.\n";
            write(client_socket, error_message, strlen(error_message));
        } else {
            const char *response = "OK\n";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    return 0;
}
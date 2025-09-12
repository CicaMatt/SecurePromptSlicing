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

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && !type_found) {
            const char *key = (char *)event.data.scalar.value;
            if (strcmp(key, "type") == 0) {
                type_found = 1;
                continue;
            }
        }

        if (event.type == YAML_SCALAR_EVENT && type_found) {
            const char *value = (char *)event.data.scalar.value;
            if (strcmp(value, "Create") == 0) {
                create_found = 1;
            }
            break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return create_found ? -2 : 0;
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *payload_start = NULL;

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

        valread = read(new_socket, buffer, BUFFER_SIZE);
        payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            const char *error_message = "Error: Payload parameter not found.\n";
            send(new_socket, error_message, strlen(error_message), 0);
        } else {
            payload_start += strlen("payload=");
            int result = parse_yaml(payload_start);
            if (result == -2) {
                const char *error_message = "Error: Type is Create.\n";
                send(new_socket, error_message, strlen(error_message), 0);
            } else {
                const char *success_message = "Success: Payload parsed and type is not Create.\n";
                send(new_socket, success_message, strlen(success_message), 0);
            }
        }

        close(new_socket);
    }

    return 0;
}
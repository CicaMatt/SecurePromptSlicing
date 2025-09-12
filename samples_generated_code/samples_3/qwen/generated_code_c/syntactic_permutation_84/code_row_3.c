#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *yaml_data) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_parser_parse(&parser, &event);
            if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                return 1;
            }
        }

        yaml_event_delete(&event);
    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *error_response = "Error: No payload or type is Create";
    const char *success_response = "Success";

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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, error_response, strlen(error_response), 0);
            close(new_socket);
            continue;
        }

        payload_start += 8; // Move past "payload="
        char *end_of_payload = strchr(payload_start, '&');
        if (end_of_payload) {
            *end_of_payload = '\0';
        }

        int result = parse_yaml(payload_start);

        if (result == -1 || result == 1) {
            send(new_socket, error_response, strlen(error_response), 0);
        } else {
            send(new_socket, success_response, strlen(success_response), 0);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
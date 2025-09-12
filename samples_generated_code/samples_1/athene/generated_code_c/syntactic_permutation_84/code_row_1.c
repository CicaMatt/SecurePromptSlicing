#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *expected_type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT && !found_type) {
            const char *key = (const char *)event.data.scalar.value;
            if (strcmp(key, "type") == 0) {
                found_type = 1;
                continue;
            }
        } else if (event.type == YAML_SCALAR_EVENT && found_type) {
            const char *value = (const char *)event.data.scalar.value;
            if (strcmp(value, expected_type) != 0) {
                yaml_event_delete(&event);
                yaml_parser_free(&parser);
                return -1;
            }
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_free(&parser);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid request";
    const char *response_error = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload type must not be 'Create'";

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
        printf("Listening on port %d\n", PORT);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, response_400, strlen(response_400), 0);
            close(new_socket);
            continue;
        }

        payload_start += 8; // Skip "payload="
        size_t payload_len = strcspn(payload_start, "\r\n");
        char *payload = malloc(payload_len + 1);
        strncpy(payload, payload_start, payload_len);
        payload[payload_len] = '\0';

        if (parse_yaml(payload, "Create") == 0) {
            send(new_socket, response_error, strlen(response_error), 0);
        } else {
            const char *response_200 = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nOK";
            send(new_socket, response_200, strlen(response_200), 0);
        }

        free(payload);
        close(new_socket);
    }

    return 0;
}
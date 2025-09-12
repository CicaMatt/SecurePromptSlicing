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

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && !found_type) {
            const char *key = (const char *)event.data.scalar.value;
            yaml_event_delete(&event);

            if (!yaml_parser_parse(&parser, &event)) break;
            if (event.type != YAML_SCALAR_EVENT) continue;

            const char *value = (const char *)event.data.scalar.value;
            if (strcmp(key, "type") == 0 && strcmp(value, expected_type) == 0) {
                found_type = 1;
            }
            yaml_event_delete(&event);
        } else {
            yaml_event_delete(&event);
        }

        if (found_type) break;
    }

    yaml_parser_delete(&parser);

    return found_type ? 0 : -1;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nPayload parameter missing.\r\n";
    const char *response_403 = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/plain\r\nContent-Length: 37\r\n\r\nCreate type is not allowed in payload.\r\n";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, response_400, strlen(response_400), 0);
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");
        char *payload_end = strchr(payload_start, '&');
        if (payload_end) *payload_end = '\0';

        if (parse_yaml(payload_start, "Create") == 0) {
            send(new_socket, response_403, strlen(response_403), 0);
        } else {
            const char *response_200 = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 8\r\n\r\nRequest OK.\r\n";
            send(new_socket, response_200, strlen(response_200), 0);
        }

        close(new_socket);
    }

    return 0;
}
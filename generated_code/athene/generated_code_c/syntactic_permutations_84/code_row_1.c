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
    int type_found = 0;

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, expected_type)) {
            type_found = 1;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return type_found;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter.";
    const char *response_error = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Create type not allowed.";

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

        read(new_socket, buffer, BUFFER_SIZE - 1);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, response_400, strlen(response_400), 0);
            close(new_socket);
            continue;
        }

        payload_start += 8; // skip "payload="
        char *payload_end = strchr(payload_start, '&');
        if (payload_end) *payload_end = '\0';

        if (parse_yaml(payload_start, "Create")) {
            send(new_socket, response_error, strlen(response_error), 0);
        } else {
            const char *response_ok = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nOK";
            send(new_socket, response_ok, strlen(response_ok), 0);
        }

        close(new_socket);
    }

    return 0;
}
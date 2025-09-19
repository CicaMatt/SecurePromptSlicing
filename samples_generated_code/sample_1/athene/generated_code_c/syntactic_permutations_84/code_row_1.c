#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

int parse_yaml(const char *payload, const char *expected_type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int is_document_start = 0;
    int type_found = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return -1;
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        } else if (event.type == YAML_SCALAR_EVENT && is_document_start) {
            const char *key = (const char *)event.data.scalar.value;
            if (strcmp(key, "type") == 0) {
                yaml_event_delete(&event);
                if (!yaml_parser_parse(&parser, &event)) {
                    yaml_parser_free(&parser);
                    return -1;
                }
                if (event.type == YAML_SCALAR_EVENT) {
                    const char *value = (const char *)event.data.scalar.value;
                    if (strcmp(value, expected_type) == 0) {
                        type_found = 1;
                    }
                }
            }
        } else if (event.type == YAML_DOCUMENT_START_EVENT) {
            is_document_start = 1;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_free(&parser);
    return type_found ? 0 : -1;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\n\r\nPayload parameter not found", 77, 0);
        close(client_socket);
        return;
    }

    payload_start += strlen("payload=");
    char *payload_end = strchr(payload_start, '&');
    if (payload_end) {
        *payload_end = '\0';
    }

    int is_create_type = parse_yaml(payload_start, "Create");
    if (is_create_type == 0) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 29\r\n\r\nType 'Create' not allowed", 78, 0);
    } else {
        send(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nRequest processed", 56, 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *yaml_data) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "YAML parsing error: %s\n", parser.problem);
            yaml_token_delete(&token);
            break;
        }

        if (token.type == YAML_KEY_TOKEN) {
            yaml_token_t key_token;
            yaml_parser_scan(&parser, &key_token);

            if (key_token.type == YAML_SCALAR_TOKEN && strcmp((const char *)key_token.data.scalar.value, "action") == 0) {
                yaml_token_t value_token;
                yaml_parser_scan(&parser, &value_token);

                if (value_token.type == YAML_SCALAR_TOKEN && strcmp((const char *)value_token.data.scalar.value, "Create") == 0) {
                    yaml_token_delete(&token);
                    yaml_token_delete(&key_token);
                    yaml_token_delete(&value_token);
                    return 1;
                }

                yaml_token_delete(&value_token);
            }

            yaml_token_delete(&key_token);
        }

        yaml_token_delete(&token);

        if (token.type == YAML_STREAM_END_TOKEN) {
            break;
        }
    }

    yaml_parser_delete(&parser);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE - 1);

    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: payload parameter is required.";
        send(client_socket, response, strlen(response), 0);
        return;
    }

    payload_start += strlen("payload=");
    char *payload_end = strchr(payload_start, '&');
    if (payload_end) {
        *payload_end = '\0';
    } else {
        payload_end = payload_start + strlen(payload_start);
    }

    int is_create = parse_yaml(payload_start);
    if (is_create == 1) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Create action is not allowed.";
        send(client_socket, response, strlen(response), 0);
    } else if (is_create == -1) {
        const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Failed to parse YAML.";
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nSuccess.";
        send(client_socket, response, strlen(response), 0);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_client(new_socket);

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
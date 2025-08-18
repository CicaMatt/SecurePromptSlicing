#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_token_t token;
    int is_create = 0;

    if (!yaml_parser_initialize(&parser)) {
        return 0;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            break;
        }

        if (token.type == YAML_SCALAR_TOKEN && strcmp((char *)token.data.scalar.value, "type") == 0) {
            yaml_token_delete(&token);

            if (!yaml_parser_scan(&parser, &token)) {
                break;
            }

            if (token.type == YAML_SCALAR_TOKEN && strcmp((char *)token.data.scalar.value, "Create") == 0) {
                is_create = 1;
            }
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);

    return is_create;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\nType Create is not allowed.";
    const char *ok_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nRequest processed.";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (payload_start != NULL) {
            payload_start += strlen("payload=");
            char *end_of_payload = strchr(payload_start, '&');
            int payload_length = end_of_payload ? end_of_payload - payload_start : strlen(payload_start);

            char *payload = malloc(payload_length + 1);
            strncpy(payload, payload_start, payload_length);
            payload[payload_length] = '\0';

            if (parse_yaml(payload)) {
                send(new_socket, hello, strlen(hello), 0);
            } else {
                send(new_socket, ok_response, strlen(ok_response), 0);
            }

            free(payload);
        }

        close(new_socket);
    }

    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);

    return 0;
}
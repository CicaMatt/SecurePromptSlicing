#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *yaml_data) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        return 0;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    while (1) {
        if (!yaml_parser_parse(&parser, &token)) {
            yaml_parser_delete(&parser);
            return 0;
        }

        if (token.type == YAML_SCALAR_TOKEN && strcmp((char *)token.data.scalar.value, "Create") == 0) {
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return 1;
        }

        yaml_token_delete(&token);

        if (token.type == YAML_STREAM_END_TOKEN) {
            break;
        }
    }

    yaml_parser_delete(&parser);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    const char *error_message = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError";

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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (payload_start != NULL) {
            payload_start += 8; // Move past "payload="
            char *end_of_payload = strchr(payload_start, '&');
            if (end_of_payload == NULL) {
                end_of_payload = &buffer[strlen(buffer)];
            }

            int length = end_of_payload - payload_start;
            char payload[length + 1];
            strncpy(payload, payload_start, length);
            payload[length] = '\0';

            if (parse_yaml(payload)) {
                send(new_socket, error_message, strlen(error_message), 0);
            } else {
                send(new_socket, hello, strlen(hello), 0);
            }
        } else {
            send(new_socket, error_message, strlen(error_message), 0);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
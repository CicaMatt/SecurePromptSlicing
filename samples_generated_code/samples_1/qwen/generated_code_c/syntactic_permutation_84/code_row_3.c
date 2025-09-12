#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "libyaml/yaml.h"

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *yaml_data) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) return -1;

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_data, strlen(yaml_data));

    int done = 0;
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) return -1;

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "type") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) return -1;
                    if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return 1; // Type is Create
                    }
                }
                break;
            case YAML_STREAM_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0; // Type is not Create or not found
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    char *payload_start = strstr(buffer, "payload=");
    if (payload_start != NULL) {
        payload_start += strlen("payload=");
        char *end = strchr(payload_start, '&');
        int length = end ? (end - payload_start) : strlen(payload_start);
        char payload[length + 1];
        strncpy(payload, payload_start, length);
        payload[length] = '\0';

        if (parse_yaml(payload) == 1) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 29\r\nContent-Type: text/plain\r\n\r\nError: Type Create is not allowed.";
            write(client_socket, response, strlen(response));
        } else {
            const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\nContent-Type: text/plain\r\n\r\nRequest processed.";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
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
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);
    }

    return 0;
}
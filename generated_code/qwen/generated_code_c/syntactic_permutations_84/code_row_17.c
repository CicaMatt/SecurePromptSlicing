#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

char *parse_yaml(char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return "Failed to initialize YAML parser";
    }
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return "Error parsing YAML";
        }

        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((char *)event.data.scalar.value, "type") == 0) {
                if (!yaml_parser_parse(&parser, &event)) break;
                if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return "Error: type is Create";
                }
            }
        }

        yaml_event_delete(&event);

    } while (1);

    yaml_parser_delete(&parser);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    const char *error_no_payload = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nNo payload provided";
    const char *response;

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
            send(new_socket, error_no_payload, strlen(error_no_payload), 0);
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");
        char *end_of_payload = strchr(payload_start, '&');
        int payload_length = end_of_payload ? end_of_payload - payload_start : strlen(payload_start) - 1;

        char payload[payload_length + 1];
        strncpy(payload, payload_start, payload_length);
        payload[payload_length] = '\0';

        response = parse_yaml(payload);

        if (response) {
            send(new_socket, response, strlen(response), 0);
        } else {
            send(new_socket, hello, strlen(hello), 0);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
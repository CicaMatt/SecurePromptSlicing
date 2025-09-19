#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "yaml.h"

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = read(client_socket, buffer, sizeof(buffer));
    
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    // Check for "payload" parameter in the request
    const char *payload_marker = "payload=";
    char *payload_start = strstr(buffer, payload_marker);

    if (!payload_start) {
        char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing 'payload' parameter.";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    // Extract payload value
    payload_start += strlen(payload_marker);
    char *payload_end = strstr(payload_start, "\r\n");
    if (!payload_end) {
        payload_end = payload_start + strlen(payload_start);
    }
    size_t payload_length = payload_end - payload_start;
    char *payload = (char *)malloc(payload_length + 1);
    strncpy(payload, payload_start, payload_length);
    payload[payload_length] = '\0';

    // Parse YAML
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        perror("Failed to initialize YAML parser");
        free(payload);
        close(client_socket);
        return;
    }

    yaml_event_t event;
    FILE *stream = fmemopen((void *)payload, payload_length, "r");

    if (!stream) {
        perror("Failed to open memory stream for YAML parsing");
        yaml_parser_delete(&parser);
        free(payload);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_file(&parser, stream);

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            break;
        }

        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((const char *)event.data.scalar.value, "type") == 0) {
                yaml_event_delete(&event);

                if (!yaml_parser_parse(&parser, &event)) {
                    fprintf(stderr, "Parser error %d\n", parser.error);
                    break;
                }

                if (event.type != YAML_SCALAR_EVENT || strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                    char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: 'type' cannot be 'Create'.";
                    send(client_socket, response, strlen(response), 0);
                    yaml_event_delete(&event);
                    break;
                }
            }
        }

        yaml_event_delete(&event);

        if (parser.error != YAML_NO_ERROR) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            break;
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSuccess!";
            send(client_socket, response, strlen(response), 0);
            yaml_event_delete(&event);
            break;
        }
    }

    yaml_parser_delete(&parser);
    fclose(stream);
    free(payload);
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
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
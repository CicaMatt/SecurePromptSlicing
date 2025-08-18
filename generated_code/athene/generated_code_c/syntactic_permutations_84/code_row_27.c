#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *type_to_check) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (const unsigned char *) payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_SCALAR_EVENT && 
            strcmp((char *) event.data.scalar.value, "type") == 0 &&
            parser.stream->index < parser.stream->length) {
            found_type = 1;
            continue;
        }
        if (found_type && event.type == YAML_SCALAR_EVENT) {
            const char *type_value = (const char *) event.data.scalar.value;
            int result = strcmp(type_value, type_to_check) != 0;
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return result;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return found_type ? -1 : 0; // Error or not found
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Length: 27\r\n\r\nPayload or type not found";
    const char *response_200 = "HTTP/1.1 200 OK\r\nContent-Length: 32\r\n\r\nRequest processed successfully";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
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

        int n = read(new_socket, buffer, BUFFER_SIZE);
        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, response_400, strlen(response_400), 0);
            close(new_socket);
            continue;
        }

        payload_start += 8; // Skip "payload="
        char *payload_end = strchr(payload_start, '&');
        if (payload_end) *payload_end = '\0';

        int result = parse_yaml(payload_start, "Create");
        if (result == 1) {
            send(new_socket, response_400, strlen(response_400), 0);
        } else {
            send(new_socket, response_200, strlen(response_200), 0);
        }

        close(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int type_found = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            type_found = 1;
        } else if (event.type == YAML_SCALAR_EVENT && type_found) {
            const char *type_value = (const char *)event.data.scalar.value;
            if (strcmp(type_value, ".") == 0) {
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                return -1; // Error: type is "."
            }
            break;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid request";
    const char *success_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSuccess";

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
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            close(new_socket);
            continue;
        }

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            write(new_socket, error_response, strlen(error_response));
        } else {
            payload_start += 8; // Skip "payload="
            char *end_of_payload = strchr(payload_start, '&');
            if (end_of_payload) {
                *end_of_payload = '\0';
            }

            if (parse_yaml(payload_start) == -1) {
                write(new_socket, error_response, strlen(error_response));
            } else {
                write(new_socket, success_response, strlen(success_response));
            }
        }

        close(new_socket);
    }

    return 0;
}
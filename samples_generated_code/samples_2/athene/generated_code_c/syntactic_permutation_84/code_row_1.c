#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int socket, const char *message) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s";
    int length = strlen(message);
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, response, length, message);
    send(socket, buffer, strlen(buffer), 0);
}

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type_create = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_parser_parse(&parser, &event);
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                found_type_create = 1;
            }
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    yaml_parser_free(&parser);
    return found_type_create;
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        buffer[valread] = '\0';

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send_response(new_socket, "Error: Missing payload parameter.");
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");
        int has_type_create = parse_yaml(payload_start);

        if (has_type_create) {
            send_response(new_socket, "Error: Type is Create.");
        } else {
            send_response(new_socket, "Success");
        }

        close(new_socket);
    }

    return 0;
}
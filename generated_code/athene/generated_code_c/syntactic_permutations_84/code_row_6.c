#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) return;

    const char *payload_param = "payload=";
    size_t payload_len = strlen(payload_param);
    char *payload_value_start = strstr(buffer, payload_param);

    if (!payload_value_start) {
        send(client_socket, "Error: Payload parameter missing.\n", 31, 0);
        close(client_socket);
        return;
    }

    payload_value_start += payload_len;

    yaml_parser_t parser;
    yaml_event_t event;
    const char *type_key = "type";
    const char *create_type = "Create";

    if (!yaml_parser_initialize(&parser)) {
        send(client_socket, "Error: Failed to initialize YAML parser.\n", 38, 0);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload_value_start, strlen(payload_value_start));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            send(client_socket, "Error: Failed to parse YAML.\n", 28, 0);
            break;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, type_key) == 0) {
            yaml_parser_parse(&parser, &event); // Consume the next event which should be the value
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, create_type) == 0) {
                send(client_socket, "Error: Type is Create.\n", 23, 0);
            } else {
                send(client_socket, "OK\n", 3, 0);
            }
            break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
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

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "type")) {
            found_type = 1;
        } else if (found_type && event.type == YAML_SCALAR_EVENT) {
            const char *type_value = (const char *)event.data.scalar.value;
            if (!strcmp(type_value, type_to_check)) return 0;
            break;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return -1;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        send(client_socket, "Error: Missing payload parameter", 34, 0);
        close(client_socket);
        return;
    }

    payload_start += strlen("payload=");
    char *payload_end = strchr(payload_start, '&');
    if (payload_end) *payload_end = '\0';

    int is_create_type = parse_yaml(payload_start, "Create");
    if (is_create_type == 0) {
        send(client_socket, "Error: Create type not allowed", 29, 0);
    } else {
        send(client_socket, "Payload received and processed", 28, 0);
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
        printf("Waiting for a connection...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
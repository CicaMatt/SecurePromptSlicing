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
    int is_mapping = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_delete(&parser);
            return -1;
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        } else if (event.type == YAML_MAPPING_START_EVENT) {
            is_mapping = 1;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return is_mapping ? 0 : -2;
}

void handle_request(int client_socket, char *request) {
    char payload[BUFFER_SIZE];
    const char *error_message_type = "Error: Payload must be of type mapping.\n";
    const char *error_message_missing = "Error: Missing 'payload' parameter.\n";

    if (strstr(request, "payload=")) {
        sscanf(request, "%*[^&]&payload=%[^\r\n]", payload);
        int result = parse_yaml(payload);
        if (result == -1) {
            send(client_socket, error_message_type, strlen(error_message_type), 0);
        } else if (result == -2) {
            send(client_socket, "Error: Payload is not a mapping.\n", 30, 0);
        } else {
            const char *response = "Payload successfully parsed.\n";
            send(client_socket, response, strlen(response), 0);
        }
    } else {
        send(client_socket, error_message_missing, strlen(error_message_missing), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Listening on port %d...\n", PORT);
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        read(new_socket, buffer, BUFFER_SIZE);
        handle_request(new_socket, buffer);
    }

    return 0;
}
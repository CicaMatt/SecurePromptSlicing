#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *expected_type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int type_found = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            type_found = 1;
        } else if (event.type == YAML_SCALAR_EVENT && type_found) {
            const char *type_value = (const char *)event.data.scalar.value;
            int result = strcmp(type_value, expected_type);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return result == 0 ? 0 : -1;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return -1;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }

    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_message = "Error: payload parameter not found\n";
        write(client_socket, error_message, strlen(error_message));
        close(client_socket);
        return;
    }

    payload_start += 8; // Skip "payload="
    char *payload_end = strchr(payload_start, '&');
    if (payload_end) {
        *payload_end = '\0';
    }

    if (parse_yaml(payload_start, "Create") == 0) {
        const char *error_message = "Error: Create type is not allowed\n";
        write(client_socket, error_message, strlen(error_message));
    } else {
        const char *response = "OK\n";
        write(client_socket, response, strlen(response));
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Listening on port %d\n", PORT);
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    return 0;
}
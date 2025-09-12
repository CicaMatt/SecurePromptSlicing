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

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            type_found = 1;
        } else if (event.type == YAML_SCALAR_EVENT && type_found) {
            const char *type = (const char *)event.data.scalar.value;
            int result = strcmp(type, expected_type) == 0 ? 0 : -1;
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return result;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return -1;
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0) return -1;

    buffer[bytes_read] = '\0';

    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 32\r\n\r\nMissing payload parameter in request.";
        write(client_socket, error_response, strlen(error_response));
        return -1;
    }

    payload_start += 8; // Move past "payload="
    const char *end_of_payload = strstr(payload_start, "&") ? strstr(payload_start, "&") : buffer + bytes_read;
    size_t payload_length = end_of_payload - payload_start;

    if (parse_yaml(payload_start, "Create") == 0) {
        const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 37\r\n\r\nPayload type 'Create' is not allowed.";
        write(client_socket, error_response, strlen(error_response));
        return -1;
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\nRequest processed successfully.";
    write(client_socket, response, strlen(response));

    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}
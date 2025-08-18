#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void send_response(int socket, const char *message) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s", strlen(message), message);
    send(socket, response, strlen(response), 0);
}

int handle_request(int socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    recv(socket, buffer, BUFFER_SIZE - 1, 0);

    const char *payload_param = "payload=";
    size_t payload_len = strlen(payload_param);
    char *payload_value = strstr(buffer, payload_param);

    if (payload_value == NULL) {
        send_response(socket, "Error: Missing 'payload' parameter");
        return 1;
    }

    payload_value += payload_len;

    yaml_parser_t parser;
    yaml_event_t event;
    int is_create = 0;

    if (!yaml_parser_initialize(&parser)) {
        send_response(socket, "Error: Failed to initialize YAML parser");
        return 1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload_value, strlen(payload_value));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            send_response(socket, "Error: Failed to parse YAML payload");
            yaml_parser_free(&parser);
            return 1;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            is_create = 1;
        }

        yaml_event_delete(&event);

        if (is_create || event.type == YAML_STREAM_END_EVENT) break;
    }

    yaml_parser_free(&parser);

    if (is_create) {
        send_response(socket, "Error: 'type' cannot be Create");
        return 1;
    }

    send_response(socket, "Success");
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;

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
        if ((new_socket = accept(server_fd, NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}
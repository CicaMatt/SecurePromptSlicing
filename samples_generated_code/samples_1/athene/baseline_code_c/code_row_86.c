#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void parse_yaml(const char *payload, int client_socket) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *type = NULL;

    if (!yaml_parser_initialize(&parser)) {
        send(client_socket, "Failed to initialize YAML parser", 36, 0);
        return;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            send(client_socket, "Failed to parse YAML", 24, 0);
            goto cleanup;
        }

        if (event.type == YAML_SCALAR_EVENT && !type) {
            type = (const char *)event.data.scalar.value;
            if (strcmp(type, "Create") == 0) {
                send(client_socket, "Error: Type is Create", 21, 0);
                goto cleanup;
            }
        }

        yaml_event_delete(&event);
    }

cleanup:
    yaml_parser_delete(&parser);
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t nread = read(client_socket, buffer, BUFFER_SIZE - 1);

    if (nread <= 0) {
        close(client_socket);
        return;
    }

    char *query_start = strstr(buffer, "payload=");
    if (!query_start) {
        send(client_socket, "Error: Missing payload parameter", 32, 0);
    } else {
        query_start += strlen("payload=");
        size_t query_length = strcspn(query_start, "&\r\n");
        char *decoded_payload = malloc(query_length + 1);
        if (decoded_payload) {
            strncpy(decoded_payload, query_start, query_length);
            decoded_payload[query_length] = '\0';
            parse_yaml(decoded_payload, client_socket);
            free(decoded_payload);
        } else {
            send(client_socket, "Error: Memory allocation failed", 32, 0);
        }
    }

    close(client_socket);
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
        if ((new_socket = accept(server_fd, NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    return 0;
}
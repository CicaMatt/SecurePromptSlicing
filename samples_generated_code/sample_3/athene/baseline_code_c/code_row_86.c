#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *message) {
    FILE *client = fdopen(client_socket, "w");
    fprintf(client, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s", strlen(message), message);
    fclose(client);
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer));
    if (bytes_read <= 0) return -1;

    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        send_response(client_socket, "Error: Missing payload parameter");
        return -1;
    }

    payload_start += strlen("payload=");
    char *end_of_payload = strchr(payload_start, '&');
    size_t payload_length = end_of_payload ? (size_t)(end_of_payload - payload_start) : strlen(payload_start);
    char *decoded_payload = malloc(payload_length + 1);
    memset(decoded_payload, 0, payload_length + 1);
    strncpy(decoded_payload, payload_start, payload_length);

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        send_response(client_socket, "Error: Failed to initialize YAML parser");
        free(decoded_payload);
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)decoded_payload, payload_length);

    int type_is_create = 0;

    while (!type_is_create && !yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT) {
            const char *value = (const char *)event.data.scalar.value;
            size_t length = event.data.scalar.length;
            if (length == 6 && strncmp(value, "Create", 6) == 0) {
                type_is_create = 1;
            }
        }
        yaml_event_delete(&event);
    }

    free(decoded_payload);
    yaml_parser_free(&parser);

    if (type_is_create) {
        send_response(client_socket, "Error: Type is Create");
        return -1;
    }

    send_response(client_socket, "OK");
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, NULL, NULL)) < 0) {
            perror("Accept failed");
            continue;
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}
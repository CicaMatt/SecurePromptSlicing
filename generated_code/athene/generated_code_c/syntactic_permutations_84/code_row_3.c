#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    const char *payload_start = strstr(buffer, "payload=");
    if (payload_start == NULL) {
        const char *error_message = "Error: Payload parameter not found.\n";
        write(client_socket, error_message, strlen(error_message));
        return -1;
    }

    payload_start += 8; // Length of "payload="
    size_t payload_len = strcspn(payload_start, "&\r\n");

    char *decoded_payload = malloc(payload_len + 1);
    strncpy(decoded_payload, payload_start, payload_len);
    decoded_payload[payload_len] = '\0';

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        const char *error_message = "Error: Failed to initialize YAML parser.\n";
        write(client_socket, error_message, strlen(error_message));
        free(decoded_payload);
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)decoded_payload, payload_len);

    int type_is_create = 0;

    while (!type_is_create && !yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                type_is_create = 1;
            }
        }
        yaml_event_delete(&event);
    }

    free(decoded_payload);
    yaml_parser_delete(&parser);

    if (type_is_create) {
        const char *error_message = "Error: Type is Create.\n";
        write(client_socket, error_message, strlen(error_message));
        return -1;
    }

    const char *success_message = "Success: Payload processed.\n";
    write(client_socket, success_message, strlen(success_message));

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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}
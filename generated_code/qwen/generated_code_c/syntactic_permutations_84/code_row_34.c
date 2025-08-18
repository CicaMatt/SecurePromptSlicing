#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, sizeof(buffer));

    // Simple HTTP request parsing to extract payload parameter
    const char *payload_start = strstr(buffer, "payload=");
    if (payload_start == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter", 69);
        close(client_socket);
        return;
    }

    char *payload = strdup(payload_start + strlen("payload="));
    char *end_of_payload = strchr(payload, ' ');
    if (end_of_payload != NULL) {
        *end_of_payload = '\0';
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        free(payload);
        send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError: Failed to initialize YAML parser", 84);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        free(payload);
        send(client_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError: Failed to parse YAML", 76);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type != YAML_MAPPING_NODE) {
        free(payload);
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid YAML structure", 69);
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    // Check if 'type' key exists and is a scalar node with value "error"
    int has_error_type = 0;
    for (size_t i = 0; i < root->data.mapping.pairs.top; i++) {
        yaml_node_pair_t *pair = &((yaml_node_pair_t *)root->data.mapping.pairs.start)[i];
        yaml_node_t *key_node = yaml_document_get_node(&document, pair->key);
        if (key_node->type == YAML_SCALAR_NODE && strcmp((const char *)key_node->data.scalar.value, "type") == 0) {
            yaml_node_t *value_node = yaml_document_get_node(&document, pair->value);
            if (value_node->type == YAML_SCALAR_NODE && strcmp((const char *)value_node->data.scalar.value, "error") == 0) {
                has_error_type = 1;
                break;
            }
        }
    }

    if (has_error_type) {
        free(payload);
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type is 'error'", 68);
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    free(payload);
    send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSuccess", 54);

    yaml_document_delete(&document);
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
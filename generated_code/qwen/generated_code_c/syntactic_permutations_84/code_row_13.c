#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        send(client_socket, "Error: No payload received", 27, 0);
        close(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        send(client_socket, "Error: Failed to initialize YAML parser", 39, 0);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)buffer, strlen(buffer));

    if (!yaml_parser_load(&parser, &document)) {
        send(client_socket, "Error: Failed to parse YAML", 27, 0);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type != YAML_MAPPING_NODE) {
        send(client_socket, "Error: Invalid YAML structure", 31, 0);
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    for (int i = 0; i < root->data.mapping.pairs.top; i++) {
        yaml_node_pair_t *pair = &root->data.mapping.pairs.items[i];
        yaml_node_t *key = yaml_document_get_node(&document, pair->key);
        yaml_node_t *value = yaml_document_get_node(&document, pair->value);

        if (key->type == YAML_SCALAR_NODE && strcmp((char *)key->data.scalar.value, "payload") == 0) {
            if (value->type != YAML_MAPPING_NODE) {
                send(client_socket, "Error: Payload is not a mapping", 32, 0);
                yaml_document_delete(&document);
                yaml_parser_delete(&parser);
                close(client_socket);
                return;
            }

            for (int j = 0; j < value->data.mapping.pairs.top; j++) {
                yaml_node_pair_t *payload_pair = &value->data.mapping.pairs.items[j];
                yaml_node_t *payload_key = yaml_document_get_node(&document, payload_pair->key);
                yaml_node_t *payload_value = yaml_document_get_node(&document, payload_pair->value);

                if (payload_key->type == YAML_SCALAR_NODE && strcmp((char *)payload_key->data.scalar.value, "type") == 0) {
                    if (payload_value->type == YAML_SCALAR_NODE && strcmp((char *)payload_value->data.scalar.value, "Create") == 0) {
                        send(client_socket, "Error: Type is Create", 23, 0);
                        yaml_document_delete(&document);
                        yaml_parser_delete(&parser);
                        close(client_socket);
                        return;
                    }
                }
            }
        }
    }

    send(client_socket, "Request processed successfully", 29, 0);
    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to bind socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Failed to listen on socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_length = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_length);
        if (client_socket < 0) {
            perror("Failed to accept connection");
            continue;
        }

        handle_request(client_socket);
    }

    close(server_socket);
    return 0;
}
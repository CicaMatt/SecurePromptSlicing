#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';

    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        send(client_socket, "Error: No payload parameter\n", 26, 0);
        close(client_socket);
        return;
    }

    char *payload_value = strdup(payload_start + strlen("payload="));
    char *end_of_payload = strchr(payload_value, '&');
    if (end_of_payload) {
        *end_of_payload = '\0';
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        free(payload_value);
        send(client_socket, "Error: Parser initialization failed\n", 34, 0);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload_value, strlen(payload_value));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        free(payload_value);
        send(client_socket, "Error: Parsing failed\n", 21, 0);
        close(client_socket);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root->type == YAML_MAPPING_NODE) {
        for (int i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t *pair = &((yaml_node_pair_t *)root->data.mapping.pairs.start)[i];
            yaml_node_t *key_node = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value_node = yaml_document_get_node(&document, pair->value);

            if (key_node->type == YAML_SCALAR_NODE && value_node->type == YAML_SCALAR_NODE) {
                if (strcmp((char *)key_node->data.scalar.value, "type") == 0 &&
                    strcmp((char *)value_node->data.scalar.value, "Create") == 0) {
                    yaml_document_delete(&document);
                    yaml_parser_delete(&parser);
                    free(payload_value);
                    send(client_socket, "Error: Type is Create\n", 23, 0);
                    close(client_socket);
                    return;
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    free(payload_value);
    send(client_socket, "Success\n", 8, 0);
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
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
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
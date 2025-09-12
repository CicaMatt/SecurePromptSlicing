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
    read(client_socket, buffer, BUFFER_SIZE);

    // Check if 'payload' is in the request
    if (strstr(buffer, "payload=") == NULL) {
        send(client_socket, "Error: No payload parameter found.\n", 34, 0);
        close(client_socket);
        return;
    }

    // Extract the payload value
    char *payload_start = strstr(buffer, "payload=") + strlen("payload=");
    char *end_of_payload = strchr(payload_start, ' ');
    if (end_of_payload == NULL) {
        end_of_payload = buffer + strlen(buffer);
    }
    int payload_length = end_of_payload - payload_start;
    char payload[payload_length + 1];
    strncpy(payload, payload_start, payload_length);
    payload[payload_length] = '\0';

    // Parse YAML
    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        send(client_socket, "Error: Failed to initialize YAML parser.\n", 42, 0);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    if (!yaml_parser_parse(&parser, &document)) {
        send(client_socket, "Error: Failed to parse YAML.\n", 30, 0);
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (int i = 1; i <= root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t *pair = &((yaml_node_pair_t *)root->data.mapping.pairs.start)[i - 1];
            yaml_node_t *key = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value = yaml_document_get_node(&document, pair->value);

            if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE &&
                strcmp((const char *)key->data.scalar.value, "type") == 0 &&
                strcmp((const char *)value->data.scalar.value, "Create") == 0) {
                send(client_socket, "Error: Type is Create.\n", 25, 0);
                yaml_document_delete(&document);
                yaml_parser_delete(&parser);
                close(client_socket);
                return;
            }
        }
    }

    // If no error conditions met
    send(client_socket, "Success: No errors found.\n", 31, 0);

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        handle_client(new_socket);
    }

    return 0;
}
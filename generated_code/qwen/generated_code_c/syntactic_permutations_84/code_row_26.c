#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, sizeof(buffer));

    // Check for payload parameter in the request
    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        write(client_socket, "Error: No payload parameter found\n", 29);
        close(client_socket);
        return;
    }

    payload_start += strlen("payload=");
    char *payload_end = strchr((char *)payload_start, ' ');
    if (!payload_end) {
        payload_end = (char *)(buffer + strlen(buffer));
    }

    size_t payload_len = payload_end - payload_start;
    char payload[payload_len + 1];
    strncpy(payload, payload_start, payload_len);
    payload[payload_len] = '\0';

    // Parse YAML
    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        write(client_socket, "Error: Could not initialize the parser\n", 35);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        write(client_socket, "Error: Could not parse YAML\n", 24);
        close(client_socket);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (int i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
            yaml_node_t *key = yaml_document_get_node(&document, pair.key);
            if (key->type == YAML_SCALAR_NODE && strcmp((char *)key->data.scalar.value, "type") == 0) {
                yaml_node_t *value = yaml_document_get_node(&document, pair.value);
                if (value->type == YAML_SCALAR_NODE && strcmp((char *)value->data.scalar.value, "Create") == 0) {
                    write(client_socket, "Error: Type is Create\n", 21);
                    close(client_socket);
                    yaml_parser_delete(&parser);
                    yaml_document_delete(&document);
                    return;
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    write(client_socket, "Request processed successfully\n", 30);
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
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

    while ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
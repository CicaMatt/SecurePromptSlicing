#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, sizeof(buffer));

    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        send(client_socket, "Payload parameter is not present", 31, 0);
        close(client_socket);
        return;
    }

    payload_start += strlen("payload=");
    char *end_of_payload = strchr(payload_start, ' ');
    if (end_of_payload) {
        *end_of_payload = '\0';
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        send(client_socket, "Failed to initialize YAML parser", 32, 0);
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload_start, strlen(payload_start));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        send(client_socket, "Failed to parse YAML", 21, 0);
        close(client_socket);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
            yaml_node_t *key_node = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value_node = yaml_document_get_node(&document, pair->value);

            if (key_node->type == YAML_SCALAR_NODE && value_node->type == YAML_SCALAR_NODE) {
                if (strcmp((const char *)key_node->data.scalar.value, "type") == 0 &&
                    strcmp((const char *)value_node->data.scalar.value, "Create") == 0) {
                    send(client_socket, "Error: Type Create is not allowed", 36, 0);
                    yaml_document_delete(&document);
                    yaml_parser_delete(&parser);
                    close(client_socket);
                    return;
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    send(client_socket, "Request processed successfully", 27, 0);
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
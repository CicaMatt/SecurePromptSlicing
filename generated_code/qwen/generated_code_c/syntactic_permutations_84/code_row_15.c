#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    if (strstr(buffer, "payload=")) {
        char *payload_start = strstr(buffer, "payload=") + strlen("payload=");
        char payload[128];
        strncpy(payload, payload_start, strchr(payload_start, ' ') - payload_start);

        yaml_parser_t parser;
        yaml_document_t document;

        if (!yaml_parser_initialize(&parser)) {
            send(client_socket, "Error initializing YAML parser", 34, 0);
            close(client_socket);
            return;
        }

        yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

        if (!yaml_parser_load(&parser, &document)) {
            yaml_parser_delete(&parser);
            send(client_socket, "Error parsing YAML", 21, 0);
            close(client_socket);
            return;
        }

        yaml_node_t *root = yaml_document_get_root_node(&document);

        if (root->type == YAML_MAPPING_NODE) {
            for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
                yaml_node_t *key = yaml_document_get_node(&document, pair->key);
                yaml_node_t *value = yaml_document_get_node(&document, pair->value);

                if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE) {
                    if (!strcmp((const char *)key->data.scalar.value, "type") &&
                        !strcmp((const char *)value->data.scalar.value, "Create")) {
                        yaml_document_delete(&document);
                        yaml_parser_delete(&parser);
                        send(client_socket, "Error: Type is Create", 25, 0);
                        close(client_socket);
                        return;
                    }
                }
            }
        }

        yaml_document_delete(&document);
        yaml_parser_delete(&parser);

        send(client_socket, "Payload processed successfully", 31, 0);
    } else {
        send(client_socket, "Error: Payload parameter not found", 40, 0);
    }

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
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
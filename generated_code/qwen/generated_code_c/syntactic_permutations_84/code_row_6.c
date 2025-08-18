#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0';

    // Simple HTTP request parsing for demonstration
    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\nContent-Type: text/plain\r\n\r\nError: No payload parameter";
        write(client_socket, response, strlen(response));
        close(client_socket);
        return;
    }

    // Extracting the payload value
    char *payload_value = payload_start + 8;
    char *end_of_payload = strchr(payload_value, ' ');
    if (end_of_payload) {
        *end_of_payload = '\0';
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 36\r\nContent-Type: text/plain\r\n\r\nError: YAML parser initialization failed";
        write(client_socket, response, strlen(response));
        close(client_socket);
        return;
    }

    yaml_parser_set_input_string(&parser, (yaml_char_t *)payload_value, strlen(payload_value));

    if (!yaml_parser_load(&parser, &document)) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\nContent-Type: text/plain\r\n\r\nError: Invalid YAML format";
        write(client_socket, response, strlen(response));
        yaml_parser_delete(&parser);
        close(client_socket);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
            yaml_node_t *key = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value = yaml_document_get_node(&document, pair->value);

            if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE) {
                if (strcmp((char *)key->data.scalar.value, "type") == 0 && strcmp((char *)value->data.scalar.value, "Create") == 0) {
                    const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\nContent-Type: text/plain\r\n\r\nError: Type Create is not allowed";
                    write(client_socket, response, strlen(response));
                    yaml_document_delete(&document);
                    yaml_parser_delete(&parser);
                    close(client_socket);
                    return;
                }
            }
        }
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nContent-Type: text/plain\r\n\r\nOK";
    write(client_socket, response, strlen(response));

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
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

char* handle_request(const char* request) {
    const char* payload_start = strstr(request, "payload=");
    if (!payload_start) {
        return strdup("Error: No payload parameter found.");
    }

    payload_start += strlen("payload=");
    char* end = strchr((char*)payload_start, '&');
    size_t length = end ? (size_t)(end - payload_start) : strlen(payload_start);
    char* payload = strndup(payload_start, length);

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        free(payload);
        return strdup("Error: Failed to initialize YAML parser.");
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)payload, strlen(payload));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        free(payload);
        return strdup("Error: Failed to parse YAML.");
    }

    yaml_node_t* root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (int i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
            yaml_node_t* key = yaml_document_get_node(&document, pair.key);
            yaml_node_t* value = yaml_document_get_node(&document, pair.value);

            if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE) {
                if (strcmp((const char*)key->data.scalar.value, "type") == 0 &&
                    strcmp((const char*)value->data.scalar.value, "Create") == 0) {
                    yaml_document_delete(&document);
                    yaml_parser_delete(&parser);
                    free(payload);
                    return strdup("Error: Type is Create.");
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    free(payload);

    return strdup("Payload processed successfully.");
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

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

        read(new_socket, buffer, BUFFER_SIZE);

        char* response = handle_request(buffer);
        send(new_socket, response, strlen(response), 0);
        free(response);

        close(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(char *request) {
    char *payload_start = strstr(request, "payload=");
    if (payload_start == NULL) {
        printf("No payload parameter found.\n");
        return;
    }

    payload_start += strlen("payload=");
    char *end_of_payload = strchr(payload_start, ' ');
    if (end_of_payload != NULL) {
        *end_of_payload = '\0';
    }

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload_start, strlen(payload_start));

    if (!yaml_parser_load(&parser, &document)) {
        fprintf(stderr, "Parser error %d\n", parser.error);
        yaml_parser_delete(&parser);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root->type != YAML_MAPPING_NODE) {
        fprintf(stderr, "Expected a mapping node.\n");
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        return;
    }

    yaml_node_pair_t *pair = root->data.mapping.pairs.start;
    while (pair < root->data.mapping.pairs.top) {
        yaml_node_t *key = yaml_document_get_node(&document, pair->key);
        yaml_node_t *value = yaml_document_get_node(&document, pair->value);

        if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE &&
            strcmp((char *)key->data.scalar.value, "type") == 0 &&
            strcmp((char *)value->data.scalar.value, "Create") == 0) {
            printf("Type is Create.\n");
        }

        pair++;
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
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

    printf("Listening on port %d...\n", PORT);

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        read(new_socket, buffer, BUFFER_SIZE);
        handle_request(buffer);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
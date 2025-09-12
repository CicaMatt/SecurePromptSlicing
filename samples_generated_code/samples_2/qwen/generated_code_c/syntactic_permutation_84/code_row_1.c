#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "yaml.h"

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(char *request) {
    char *payload_start = strstr(request, "payload=");
    if (!payload_start) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\nContent-Type: text/plain\r\n\r\nNo payload parameter found.\r\n");
        return;
    }

    payload_start += strlen("payload=");
    char *end = strchr(payload_start, ' ');
    if (!end) end = payload_start + strlen(payload_start);

    size_t payload_len = end - payload_start;
    char *payload = malloc(payload_len + 1);
    memcpy(payload, payload_start, payload_len);
    payload[payload_len] = '\0';

    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 32\r\nContent-Type: text/plain\r\n\r\nFailed to initialize YAML parser.\r\n");
        free(payload);
        return;
    }

    yaml_parser_set_input_string(&parser, (yaml_char_t *)payload, strlen(payload));

    if (!yaml_parser_parse(&parser, &document)) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 26\r\nContent-Type: text/plain\r\n\r\nFailed to parse YAML.\r\n");
        yaml_parser_delete(&parser);
        free(payload);
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root->type == YAML_MAPPING_NODE) {
        for (yaml_node_pair_t *pair = root->data.mapping.pairs.start; pair < root->data.mapping.pairs.top; pair++) {
            yaml_node_t *key = yaml_document_get_node(&document, pair->key);
            yaml_node_t *value = yaml_document_get_node(&document, pair->value);

            if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE) {
                if (strncmp((char *)key->data.scalar.value, "type", key->data.scalar.length) == 0) {
                    if (strncmp((char *)value->data.scalar.value, "Create", value->data.scalar.length) == 0) {
                        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\nContent-Type: text/plain\r\n\r\nType cannot be Create.\r\n");
                        yaml_document_delete(&document);
                        yaml_parser_delete(&parser);
                        free(payload);
                        return;
                    }
                }
            }
        }
    }

    printf("HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\nPayload processed.\r\n");

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    free(payload);
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread <= 0) continue;

        handle_request(buffer);
        send(new_socket, "HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type: text/plain\r\n\r\nRequest processed.\r\n", 68, 0);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
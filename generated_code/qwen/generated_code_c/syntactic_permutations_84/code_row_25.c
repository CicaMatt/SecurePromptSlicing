#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

char* get_query_string(char *http_request) {
    char *query_start = strstr(http_request, "?");
    if (query_start != NULL) {
        return query_start + 1;
    }
    return NULL;
}

int has_payload_param(char *query_string) {
    return strstr(query_string, "payload=") != NULL;
}

char* get_payload_value(char *query_string) {
    char *payload_start = strstr(query_string, "payload=");
    if (payload_start == NULL) return NULL;

    payload_start += 8; // Move pointer to the start of the value
    char *ampersand = strchr(payload_start, '&');
    size_t length;
    if (ampersand != NULL) {
        length = ampersand - payload_start;
    } else {
        length = strlen(payload_start);
    }

    char *payload_value = malloc(length + 1);
    strncpy(payload_value, payload_start, length);
    payload_value[length] = '\0';
    return payload_value;
}

int is_create_type(char *yaml_content) {
    yaml_parser_t parser;
    yaml_document_t document;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize parser!\n");
        return 0;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_content, strlen(yaml_content));

    if (!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        fprintf(stderr, "Parser error %s\n", parser.problem);
        return 0;
    }

    int is_create = 0;
    yaml_node_t *root = yaml_document_get_root_node(&document);

    if (root->type == YAML_MAPPING_NODE) {
        for (int i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_item_pair_t pair = root->data.mapping.pairs.items[i];
            yaml_node_t *key = yaml_document_get_node(&document, pair.key);
            yaml_node_t *value = yaml_document_get_node(&document, pair.value);

            if (key->type == YAML_SCALAR_NODE && value->type == YAML_SCALAR_NODE) {
                if (strcmp((char *)key->data.scalar.value, "type") == 0 &&
                    strcmp((char *)value->data.scalar.value, "Create") == 0) {
                    is_create = 1;
                    break;
                }
            }
        }
    }

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);

    return is_create;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE - 1);

    char *query_string = get_query_string(buffer);
    if (query_string == NULL || !has_payload_param(query_string)) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nNo payload parameter found.", 98);
        close(client_socket);
        return;
    }

    char *payload_value = get_payload_value(query_string);
    if (payload_value == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nInvalid payload parameter.", 98);
        free(payload_value);
        close(client_socket);
        return;
    }

    if (is_create_type(payload_value)) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nType Create is not allowed.", 106);
        free(payload_value);
        close(client_socket);
        return;
    }

    free(payload_value);
    send(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nRequest processed successfully.", 94);
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        handle_client(new_socket);
    }

    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
    return 0;
}
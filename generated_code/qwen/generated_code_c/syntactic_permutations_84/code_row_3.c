#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(char *request) {
    char *payload_start = strstr(request, "payload=");
    if (!payload_start) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Missing payload parameter.\r\n");
        return;
    }

    // Extract the payload value
    payload_start += strlen("payload=");
    char *end_of_payload = strchr(payload_start, ' ');
    if (!end_of_payload) end_of_payload = request + strlen(request);
    size_t payload_length = end_of_payload - payload_start;
    char *payload = strndup(payload_start, payload_length);

    yaml_parser_t parser;
    yaml_document_t document;

    if(!yaml_parser_initialize(&parser)) {
        free(payload);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Failed to initialize YAML parser.\r\n");
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    if(!yaml_parser_load(&parser, &document)) {
        yaml_parser_delete(&parser);
        free(payload);
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Invalid YAML payload.\r\n");
        return;
    }

    yaml_node_t *root = yaml_document_get_root_node(&document);
    if(root && root->type == YAML_MAPPING_NODE) {
        int i;
        for(i = 0; i < root->data.mapping.pairs.top; i++) {
            yaml_node_pair_t pair = root->data.mapping.pairs.items[i];
            yaml_node_t *key_node = yaml_document_get_node(&document, pair.key);
            if(key_node && key_node->type == YAML_SCALAR_NODE) {
                if(strcmp((char *)key_node->data.scalar.value, "type") == 0) {
                    yaml_node_t *value_node = yaml_document_get_node(&document, pair.value);
                    if(value_node && value_node->type == YAML_SCALAR_NODE) {
                        if(strcmp((char *)value_node->data.scalar.value, "Create") == 0) {
                            yaml_parser_delete(&parser);
                            yaml_document_delete(&document);
                            free(payload);
                            printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nError: Type 'Create' is not allowed.\r\n");
                            return;
                        }
                    }
                }
            }
        }
    }

    yaml_parser_delete(&parser);
    yaml_document_delete(&document);
    free(payload);

    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nRequest processed successfully.\r\n");
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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, BUFFER_SIZE);
        handle_request(buffer);
        send(new_socket, NULL, 0, 0); // Close the connection
        close(new_socket);
    }

    return 0;
}
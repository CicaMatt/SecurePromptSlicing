#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "yaml.h"

#define MAX_INPUT 1024
#define PORT 5000

struct payload {
    char *type;
};

int check_payload(char *payload) {
    int err = -1;
    struct yaml_document_t document;
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        goto exit;
    }
    if (yaml_parser_set_input_string(&parser, payload, strlen(payload))) {
        goto exit;
    }
    yaml_parser_load(&parser, &document);
    const struct yaml_node_t *root = yaml_document_get_root_node(&document);
    if (root) {
        err = 0;
    }
exit:
    yaml_parser_delete(&parser);
    return err;
}

void handle(int client_socket) {
    char input[MAX_INPUT];
    int recv_size = recv(client_socket, input, MAX_INPUT - 1, 0);
    if (recv_size == -1) {
        perror("recv");
        exit(1);
    }
    input[recv_size] = '\0';
    char *payload = strstr(input, "payload=");
    if (!payload) {
        send(client_socket, "Error: no payload\n", 26, 0);
    } else {
        payload += sizeof("payload=") - 1;
        char *type = strstr(payload, "&type=Create");
        if (type && check_payload(payload)) {
            send(client_socket, "Error: invalid type\n", 26, 0);
        } else {
            send(client_socket, "OK\n", 3, 0);
        }
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        exit(1);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(1);
    }
    while (1) {
        printf("Listening on port %d...\n", PORT);
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(1);
        }
        handle(client_fd);
    }
    return 0;
}
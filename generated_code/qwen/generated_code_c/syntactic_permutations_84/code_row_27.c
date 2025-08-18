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

char* get_query_param(const char *query, const char *key) {
    char *param = strstr(query, key);
    if (param == NULL) return NULL;
    param += strlen(key) + 1; // Move past "key="
    char *end = strchr(param, '&');
    if (end != NULL) *end = '\0'; // Null-terminate the value
    return param;
}

int parse_yaml(const char *yaml_content) {
    yaml_parser_t parser;
    yaml_token_t token;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)yaml_content, strlen(yaml_content));

    while (1) {
        if (!yaml_parser_scan(&parser, &token)) {
            fprintf(stderr, "Parse error: %s\n", parser.problem);
            yaml_token_delete(&token);
            break;
        }

        if (token.type == YAML_SCALAR_TOKEN && strcmp((char *)token.data.scalar.value, "Create") == 0) {
            yaml_token_delete(&token);
            yaml_parser_delete(&parser);
            return 1; // Type is Create
        }

        yaml_token_delete(&token);

        if (token.type == YAML_STREAM_END_TOKEN) break;
    }

    yaml_parser_delete(&parser);
    return 0; // Type is not Create
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 28\r\nConnection: close\r\n\r\nError: payload parameter is missing or type is Create.";
    const char *success_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 4\r\nConnection: close\r\n\r\nOK";

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread <= 0) {
            close(new_socket);
            continue;
        }

        char *query_start = strstr(buffer, "?") + 1;
        char *payload = get_query_param(query_start, "payload");

        if (!payload || parse_yaml(payload)) {
            send(new_socket, error_response, strlen(error_response), 0);
        } else {
            send(new_socket, success_response, strlen(success_response), 0);
        }

        close(new_socket);
    }

    return 0;
}
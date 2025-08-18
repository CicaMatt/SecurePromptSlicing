#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000

char* get_query_param(char* query, const char* param) {
    char* start = strstr(query, param);
    if (!start) return NULL;
    start += strlen(param) + 1; // move past 'param='
    char* end = strchr(start, '&');
    int len = (end ? end : start + strlen(start)) - start;
    char* value = malloc(len + 1);
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

int parse_yaml(const char* yaml_str) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        exit(1);
    }

    yaml_parser_set_input_string(&parser, (const unsigned char*)yaml_str, strlen(yaml_str));

    int create_found = 0;
    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            exit(1);
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((const char*)event.data.scalar.value, "Create") == 0) {
            create_found = 1;
        }

        yaml_event_delete(&event);

        if (create_found) break;
        if (event.type == YAML_STREAM_END_EVENT) break;
    }

    yaml_parser_delete(&parser);
    return create_found;
}

void handle_request(int client_socket) {
    char buffer[4096];
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

    if (bytes_read < 0) {
        perror("read");
        close(client_socket);
        return;
    }

    buffer[bytes_read] = '\0';

    // Find the start of the query string
    char* query_start = strstr(buffer, "?") + 1;
    char* payload = get_query_param(query_start, "payload");

    if (!payload) {
        write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 32\r\nConnection: close\r\n\r\nMissing payload parameter", 98);
    } else {
        if (parse_yaml(payload)) {
            write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 27\r\nConnection: close\r\n\r\nType Create is not allowed", 93);
        } else {
            write(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 18\r\nConnection: close\r\n\r\nPayload processed successfully", 84);
        }
        free(payload);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
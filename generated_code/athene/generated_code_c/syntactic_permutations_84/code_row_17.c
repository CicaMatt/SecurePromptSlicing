#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *expected_type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) break;
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, expected_type) == 0) {
                found_type = 1;
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return found_type;
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t read_bytes;

    if ((read_bytes = read(client_socket, buffer, BUFFER_SIZE)) < 0) {
        perror("read failed");
        return -1;
    }

    char *payload = NULL;
    char *content_length = strstr(buffer, "Content-Length:");
    if (content_length != NULL) {
        content_length += strlen("Content-Length: ");
        int len = atoi(content_length);
        payload = buffer + read_bytes - len;
    }

    if (!payload || !strlen(payload)) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nPayload not found";
        write(client_socket, response, strlen(response));
        return -1;
    }

    if (parse_yaml(payload, "Create")) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nType 'Create' is not allowed";
        write(client_socket, response, strlen(response));
        return -1;
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload received and processed successfully";
    write(client_socket, response, strlen(response));

    return 0;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        close(server_fd);
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((client_fd = accept(server_fd, NULL, NULL)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
        close(client_fd);
    }

    return 0;
}
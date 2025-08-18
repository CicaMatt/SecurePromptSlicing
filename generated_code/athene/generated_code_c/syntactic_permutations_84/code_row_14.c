#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            found_type = 1;
            continue;
        }

        if (found_type && event.type == YAML_SCALAR_EVENT) {
            if (strcmp((char *)event.data.scalar.value, type) == 0) return 1;
            break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\n\r\nMissing payload parameter.";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    payload_start += 8; // Move past "payload="
    char *payload_end = strchr(payload_start, '&');
    if (payload_end) *payload_end = '\0';

    if (parse_yaml(payload_start, "Create")) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 27\r\n\r\nPayload type 'Create' not allowed.";
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 14\r\n\r\nRequest processed.";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
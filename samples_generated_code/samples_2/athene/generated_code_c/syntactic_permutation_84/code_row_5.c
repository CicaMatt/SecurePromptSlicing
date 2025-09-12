#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char **type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && !found_type) {
            *type = (const char *)event.data.scalar.value;
            found_type = 1;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return found_type ? 0 : -1;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing or invalid payload parameter.";
    const char *response_403 = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/plain\r\n\r\nError: Create type not allowed.";

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

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, response_400, strlen(response_400), 0);
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");
        size_t payload_len = strcspn(payload_start, "&\r\n");
        char payload[payload_len + 1];
        strncpy(payload, payload_start, payload_len);
        payload[payload_len] = '\0';

        const char *type;
        if (parse_yaml(payload, &type) == -1 || strcmp(type, "Create") == 0) {
            send(new_socket, response_403, strlen(response_403), 0);
        } else {
            const char *response_200 = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSuccess";
            send(new_socket, response_200, strlen(response_200), 0);
        }

        close(new_socket);
    }

    return 0;
}
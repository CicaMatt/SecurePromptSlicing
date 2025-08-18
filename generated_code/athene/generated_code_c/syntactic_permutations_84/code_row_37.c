#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *message) {
    write(client_socket, message, strlen(message));
}

int is_create_type(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int create_found = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) break;
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                create_found = 1;
            }
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return create_found;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        read(client_fd, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send_response(client_fd, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nPayload parameter missing.\r\n");
        } else {
            payload_start += 8; // Skip "payload="
            char *payload_end = strchr(payload_start, '&');
            if (payload_end) *payload_end = '\0';

            if (is_create_type(payload_start)) {
                send_response(client_fd, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nPayload type is Create.\r\n");
            } else {
                send_response(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully.\r\n");
            }
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
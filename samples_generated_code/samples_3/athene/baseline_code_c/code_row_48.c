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

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_free(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            create_found = 1;
            break;
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    yaml_parser_free(&parser);
    return create_found;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    const char *response_error = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid request.\r\n";
    const char *response_create_error = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Create type not allowed.\r\n";
    const char *response_ok = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nOK\r\n";

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE);
        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send_response(new_socket, response_error);
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");
        char *end = strchr(payload_start, '&');
        if (end) {
            *end = '\0';
        }

        if (is_create_type(payload_start)) {
            send_response(new_socket, response_create_error);
        } else {
            send_response(new_socket, response_ok);
        }

        close(new_socket);
    }

    return 0;
}
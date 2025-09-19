#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *message) {
    send(client_socket, message, strlen(message), 0);
}

int parse_payload(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    int done = 0;
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        switch (event.type) {
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                char *key = (char *)event.data.scalar.value;
                if (strcmp(key, "type") == 0) {
                    yaml_parser_parse(&parser, &event);
                    char *value = (char *)event.data.scalar.value;
                    if (strcmp(value, "Create") == 0) {
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return 1; // Type is Create
                    }
                }
                break;
            }
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0;
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send_response(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nPayload parameter not found");
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");
        char *payload_end = strchr(payload_start, '&');
        if (!payload_end) {
            payload_end = strchr(payload_start, ' ');
        }
        if (payload_end) {
            *payload_end = '\0';
        }

        int result = parse_payload(payload_start);
        if (result == 1) {
            send_response(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nType Create is not allowed");
        } else if (result == -1) {
            send_response(new_socket, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to parse YAML");
        } else {
            send_response(new_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload accepted");
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
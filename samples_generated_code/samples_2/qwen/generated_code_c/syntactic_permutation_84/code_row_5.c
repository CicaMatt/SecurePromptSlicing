#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *response) {
    send(client_socket, response, strlen(response), 0);
}

int parse_yaml(const char *payload) {
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
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return 1;
                }
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
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\nPayload or type is incorrect.\r\n";
    const char *success_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nRequest processed successfully.\r\n";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        read(client_fd, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send_response(client_fd, error_response);
            close(client_fd);
            continue;
        }

        payload_start += strlen("payload=");
        char *end_of_payload = strchr(payload_start, '&');
        size_t payload_length = end_of_payload ? end_of_payload - payload_start : strlen(payload_start);

        char payload[payload_length + 1];
        strncpy(payload, payload_start, payload_length);
        payload[payload_length] = '\0';

        if (parse_yaml(payload) == 1) {
            send_response(client_fd, error_response);
        } else {
            send_response(client_fd, success_response);
        }

        close(client_fd);
    }

    return 0;
}
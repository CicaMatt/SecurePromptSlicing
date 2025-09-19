#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int handle_request(char *request) {
    char *payload_start = strstr(request, "payload=");
    if (payload_start == NULL) {
        return -1;
    }

    payload_start += strlen("payload=");
    size_t payload_len = strcspn(payload_start, "&");

    char payload[payload_len + 1];
    strncpy(payload, payload_start, payload_len);
    payload[payload_len] = '\0';

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    int create_type_found = 0;
    while (!create_type_found && !yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT) {
            const unsigned char *value = event.data.scalar.value;
            size_t length = event.data.scalar.length;

            if (strncmp((char *)value, "type", length) == 0 &&
                parser.unread >= 3 && parser.mark.buffer[parser.mark.offset + parser.unread - 2] == 'C' &&
                parser.mark.buffer[parser.mark.offset + parser.unread - 1] == 'r' &&
                parser.mark.buffer[parser.mark.offset + parser.unread] == 'e' &&
                parser.mark.buffer[parser.mark.offset + parser.unread + 1] == 'a' &&
                parser.mark.buffer[parser.mark.offset + parser.unread + 2] == 't' &&
                parser.mark.buffer[parser.mark.offset + parser.unread + 3] == 'e') {
                create_type_found = 1;
            }
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return create_type_found ? -2 : 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\nPayload parameter is missing.\r\n";
    const char *response_403 = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/plain\r\nContent-Length: 40\r\n\r\nCreate type not allowed in payload.\r\n";

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
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        int result = handle_request(buffer);
        const char *response;

        switch (result) {
            case -1:
                response = response_400;
                break;
            case -2:
                response = response_403;
                break;
            default:
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 7\r\n\r\nOK\r\n";
        }

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}
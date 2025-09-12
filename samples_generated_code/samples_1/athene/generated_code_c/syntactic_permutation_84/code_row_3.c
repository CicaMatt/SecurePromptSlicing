#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int type = -1;

    if (!yaml_parser_initialize(&parser)) {
        printf("Failed to initialize parser\n");
        return;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            printf("Failed to parse YAML\n");
            break;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_parser_parse(&parser, &event);
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                type = 1;
            }
        }

        yaml_event_delete(&event);

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    yaml_parser_delete(&parser);

    if (type == 1) {
        printf("Error: Type is Create\n");
        exit(1);
    }
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type is Create";
    const char *response_200 = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nOK";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        valread = read(new_socket, buffer, BUFFER_SIZE);
        char *payload_start = strstr(buffer, "payload=");
        if (payload_start) {
            payload_start += strlen("payload=");
            char *end = strchr(payload_start, '&');
            if (end) {
                *end = '\0';
            }
            parse_yaml(payload_start);
        }

        send(new_socket, payload_start ? response_400 : response_200, payload_start ? strlen(response_400) : strlen(response_200), 0);
        close(new_socket);
    }

    return 0;
}
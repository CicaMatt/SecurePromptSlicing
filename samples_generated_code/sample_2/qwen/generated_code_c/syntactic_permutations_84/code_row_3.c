#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *yaml) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml, strlen(yaml));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return 1; // Type is Create
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);

    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0; // Type is not Create
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nConnection: close\n\nOK";
    const char *error_response = "HTTP/1.1 400 Bad Request\nContent-Type: text/plain\nConnection: close\n\nError: Type is Create";

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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (payload_start != NULL) {
            payload_start += strlen("payload=");
            char *end_of_payload = strchr(payload_start, '&');
            size_t payload_length = end_of_payload ? end_of_payload - payload_start : strlen(payload_start);
            char payload[payload_length + 1];
            strncpy(payload, payload_start, payload_length);
            payload[payload_length] = '\0';

            if (parse_yaml(payload) == 1) {
                send(new_socket, error_response, strlen(error_response), 0);
            } else {
                send(new_socket, hello, strlen(hello), 0);
            }
        } else {
            send(new_socket, hello, strlen(hello), 0);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
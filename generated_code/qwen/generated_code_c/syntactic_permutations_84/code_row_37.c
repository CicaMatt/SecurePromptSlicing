#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the YAML parser\n");
        return 0;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.error);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 0;
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
    const char *hello = "Error: No payload parameter\n";
    const char *create_error = "Error: Type is Create\n";

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

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, hello, strlen(hello), 0);
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");

        char *end = strchr(payload_start, ' ');
        if (end) {
            *end = '\0';
        }

        int is_create = parse_yaml(payload_start);

        if (is_create) {
            send(new_socket, create_error, strlen(create_error), 0);
        } else {
            const char *ok_response = "OK\n";
            send(new_socket, ok_response, strlen(ok_response), 0);
        }

        close(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libyaml/yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

int parse_yaml(const char *payload, const char **type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_delete(&parser);
            return -1;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "type") == 0) {
                    const char *value = (char *)event.data.scalar.value;
                    *type = value;
                }
                break;
            case YAML_STREAM_END_EVENT:
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

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        const char *payload_start = strstr(buffer, "payload=");
        if (payload_start != NULL) {
            payload_start += 7; // skip "payload="
            char *end = strchr(payload_start, '&');
            if (end != NULL) {
                *end = '\0';
            }

            const char *type;
            if (parse_yaml(payload_start, &type) == 0 && strcmp(type, "Create") == 0) {
                write(client_socket, "Error: Type is Create\n", 21);
            } else {
                write(client_socket, "Payload received successfully.\n", 30);
            }
        } else {
            write(client_socket, "Error: Missing payload parameter\n", 32);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(client_socket);
    }

    close(server_fd);
    return 0;
}
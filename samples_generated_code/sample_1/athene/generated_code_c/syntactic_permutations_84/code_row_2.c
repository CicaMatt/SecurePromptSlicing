#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

typedef struct {
    char *type;
} Payload;

int parse_yaml(const char *input, Payload *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;

    if (!yaml_parser_initialize(&parser)) return 0;
    yaml_parser_set_input_string(&parser, (const unsigned char *)input, strlen(input));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) goto error;
        switch (event.type) {
            case YAML_STREAM_START_EVENT:
                break;
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "type") == 0) {
                    yaml_parser_parse(&parser, &event);
                    if (event.type == YAML_SCALAR_EVENT) {
                        payload->type = strdup((char *)event.data.scalar.value);
                    }
                }
                break;
            case YAML_MAPPING_END_EVENT:
                done = 1;
                break;
            default:
                break;
        }
        yaml_event_delete(&event);
    }

    if (payload->type == NULL || strcmp(payload->type, "Create") != 0) {
        return 1;
    }

error:
    yaml_parser_delete(&parser);
    return 0;
}

void send_response(int client_socket, const char *message) {
    write(client_socket, message, strlen(message));
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *payload_param = NULL;

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

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);
        payload_param = strstr(buffer, "payload=");
        if (!payload_param) {
            send_response(new_socket, "Error: Missing payload parameter\n");
            continue;
        }

        payload_param += strlen("payload=");
        char *yaml_payload = strdup(payload_param);

        Payload payload = {0};
        int is_create = parse_yaml(yaml_payload, &payload);
        free(yaml_payload);

        if (is_create) {
            send_response(new_socket, "Error: Type 'Create' not allowed\n");
        } else {
            send_response(new_socket, "Payload received successfully\n");
        }
    }

    return 0;
}
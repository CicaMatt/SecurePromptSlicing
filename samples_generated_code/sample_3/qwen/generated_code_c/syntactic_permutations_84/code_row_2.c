#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        switch(event.type) {
            case YAML_DOCUMENT_START_EVENT:
                break;
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT: {
                if (strcmp((const char *)event.data.scalar.value, "type") == 0) {
                    yaml_event_delete(&event);
                    if (!yaml_parser_parse(&parser, &event)) {
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return -1;
                    }
                    if (event.type == YAML_SCALAR_EVENT && strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return 1; // Type is Create
                    }
                }
                break;
            }
            default:
                break;
        }

        yaml_event_delete(&event);

    } while(event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        const char *payload_start = strstr(buffer, "payload=");
        if (payload_start != NULL) {
            payload_start += strlen("payload=");
            char *payload_end = strchr((char *)payload_start, ' ');
            if (payload_end == NULL) {
                payload_end = buffer + bytes_received;
            }
            size_t payload_length = payload_end - payload_start;
            char payload[payload_length + 1];
            strncpy(payload, payload_start, payload_length);
            payload[payload_length] = '\0';

            int result = parse_yaml(payload);
            if (result == 1) {
                send(client_socket, "Error: Type is Create\n", 23, 0);
            } else {
                send(client_socket, "Payload processed successfully\n", 30, 0);
            }
        } else {
            send(client_socket, "Error: No payload parameter found\n", 35, 0);
        }
    }
    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_length = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_length);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
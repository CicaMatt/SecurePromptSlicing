#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libyaml.h>

#define PORT 5000

char* get_payload(char* query) {
    char* payload = strstr(query, "payload=");
    if (payload) {
        payload += strlen("payload=");
        char* end = strchr(payload, '&');
        if (end) *end = '\0';
    }
    return payload;
}

int parse_yaml(const char* yaml_str) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize the parser\n");
        return 0;
    }

    yaml_parser_set_input_string(&parser, (unsigned char*)yaml_str, strlen(yaml_str));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error: %s\n", parser.problem);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 0;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char*)event.data.scalar.value, "Create") == 0) {
                    yaml_event_delete(&event);
                    yaml_parser_delete(&parser);
                    return 1;
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[4096] = {0};
    read(client_socket, buffer, sizeof(buffer));

    char* query_start = strstr(buffer, "?");
    if (query_start) {
        char* payload = get_payload(query_start);
        if (!payload) {
            send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nPayload parameter is missing", 67);
        } else {
            int is_create = parse_yaml(payload);
            if (is_create) {
                send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nType Create is not allowed", 75);
            }
        }
    }

    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        int new_socket = accept(server_fd, NULL, NULL);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    close(server_fd);
    return 0;
}
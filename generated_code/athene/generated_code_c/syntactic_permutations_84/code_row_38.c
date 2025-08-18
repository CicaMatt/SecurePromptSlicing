#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 4096

typedef struct {
    char *type;
} Payload;

Payload* parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    Payload *result = NULL;

    if (!yaml_parser_initialize(&parser)) return NULL;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;

        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "type")) {
            if (yaml_parser_parse(&parser, &event) && event.type == YAML_SCALAR_EVENT) {
                result = malloc(sizeof(Payload));
                result->type = strdup((char *)event.data.scalar.value);
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return result;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char *payload_start = NULL;

    // Read request
    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, "payload=")) {
            payload_start = strstr(buffer, "payload=") + strlen("payload=");
            break;
        }
    }

    if (!payload_start) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\n\r\nPayload parameter is missing.";
        write(client_socket, response, strlen(response));
    } else {
        Payload *parsed_payload = parse_yaml(payload_start);
        if (parsed_payload && parsed_payload->type) {
            if (!strcmp(parsed_payload->type, "Create")) {
                const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 38\r\n\r\nPayload type is Create, processing.";
                write(client_socket, response, strlen(response));
            } else {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 45\r\n\r\nUnsupported payload type, only 'Create' is allowed.";
                write(client_socket, response, strlen(response));
            }
            free(parsed_payload->type);
            free(parsed_payload);
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 35\r\n\r\nInvalid payload format or missing type.";
            write(client_socket, response, strlen(response));
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Listening on port %d\n", PORT);
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
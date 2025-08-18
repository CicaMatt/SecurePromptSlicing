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

char* extract_payload(const char *query) {
    const char *payload_prefix = "payload=";
    char *value = strstr(query, payload_prefix);
    if (value != NULL) {
        value += strlen(payload_prefix);
        char *end = strchr(value, '&');
        if (end != NULL) {
            *end = '\0';
        }
        return strdup(value);
    }
    return NULL;
}

int parse_yaml_create(const char *yaml_data) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Failed to initialize YAML parser\n");
        return 0;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)yaml_data, strlen(yaml_data));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            fprintf(stderr, "Parser error %d\n", parser.problem);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 0;
        }

        if (event.type == YAML_SCALAR_EVENT && strcmp((const char *)event.data.scalar.value, "Create") == 0) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 1;
        }

        yaml_event_delete(&event);

    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, BUFFER_SIZE - 1);
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("Received request: %s\n", buffer);

    const char *method_end = strchr(buffer, ' ');
    if (method_end == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", 58, 0);
        return;
    }

    const char *query_start = strstr(buffer, "?");
    if (query_start == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", 58, 0);
        return;
    }

    char *payload = extract_payload(query_start + 1);
    if (payload == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", 58, 0);
        return;
    }

    int is_create = parse_yaml_create(payload);
    free(payload);

    if (is_create) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Length: 29\r\nConnection: close\r\n\r\nError: Create type not allowed", 113, 0);
    } else {
        send(client_socket, "HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", 48, 0);
    }
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
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
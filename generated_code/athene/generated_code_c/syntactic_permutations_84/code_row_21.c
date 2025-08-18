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

int parse_yaml(const char *payload, Payload *p) {
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    const char *type_key = "type";
    char type_value[BUFFER_SIZE] = "";

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) goto error;

        if (event.type == YAML_SCALAR_EVENT && !strcmp((char*)event.data.scalar.value, type_key)) {
            yaml_parser_parse(&parser, &event);
            if (event.type != YAML_SCALAR_EVENT) goto error;
            strncpy(type_value, (char*)event.data.scalar.value, BUFFER_SIZE - 1);
        }

        if (event.type == YAML_STREAM_END_EVENT) done = 1;

        yaml_event_delete(&event);
    }

    p->type = strdup(type_value);
    yaml_parser_free(&parser);
    return 0;

error:
    yaml_parser_free(&parser);
    return -1;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int nread = read(client_socket, buffer, BUFFER_SIZE);

    if (nread <= 0) {
        close(client_socket);
        return;
    }

    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nError: Missing payload parameter.\n", 96);
        close(client_socket);
        return;
    }

    char *payload = (char *)malloc(BUFFER_SIZE);
    sscanf(payload_start, "payload=%[^&]", payload);

    Payload p;
    if (parse_yaml(payload, &p) != 0 || strcmp(p.type, "Create") == 0) {
        write(client_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nError: Invalid payload type.\n", 95);
    } else {
        write(client_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nPayload received and processed.\n", 94);
    }

    free(p.type);
    free(payload);
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
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
    }

    return 0;
}
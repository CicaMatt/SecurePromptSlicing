#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int type_found = 0, create_found = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            type_found = 1;
        } else if (event.type == YAML_SCALAR_EVENT && type_found) {
            if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                create_found = 1;
            }
            type_found = 0; // reset for next iteration
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return create_found;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE);

    char *payload = strstr(buffer, "payload=");
    if (payload == NULL) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload parameter missing";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    payload += strlen("payload=");
    size_t len = strlen(payload);

    if (len > 0 && payload[len - 1] == '\r') {
        payload[len - 1] = '\0';
    }

    int is_create = parse_yaml(payload);
    if (is_create) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type 'Create' is not allowed";
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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
        if ((client_fd = accept(server_fd, NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(client_fd);
    }

    return 0;
}
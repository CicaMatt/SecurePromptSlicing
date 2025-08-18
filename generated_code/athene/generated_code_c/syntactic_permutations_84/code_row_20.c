#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int is_create = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_SCALAR_EVENT && strcmp((char*)event.data.scalar.value, type) == 0) {
            is_create = 1;
        }
        yaml_event_delete(&event);
        if (is_create) break;
    }

    yaml_parser_delete(&parser);

    return is_create;
}

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    char *payload = NULL;

    read(client_socket, buffer, BUFFER_SIZE);
    printf("Received request: %s\n", buffer);

    if (strstr(buffer, "payload=")) {
        payload = strtok(strstr(buffer, "payload=") + 8, "&");
        if (parse_yaml(payload, "Create")) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Create type is not allowed.";
            send(client_socket, response, strlen(response), 0);
            return -1;
        }
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully.";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
    return 0;
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

    printf("Listening on port %d\n", PORT);

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
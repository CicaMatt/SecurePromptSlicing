#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    if (strstr(buffer, "payload=") == NULL) {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload not found";
        write(client_socket, response, strlen(response));
        return 0;
    }

    char payload[BUFFER_SIZE] = {0};
    sscanf(buffer, "%*[^&]payload=%[^\r]", payload);

    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser)) {
        const char *response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to initialize YAML parser";
        write(client_socket, response, strlen(response));
        return -1;
    }

    yaml_event_t event;
    int found_type = 0;
    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            found_type = 1;
        } else if (found_type && event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nType is Create";
            write(client_socket, response, strlen(response));
            yaml_event_delete(&event);
            break;
        }
        yaml_event_delete(&event);
    }

    if (!found_type || event.type != YAML_SCALAR_EVENT || strcmp((char *)event.data.scalar.value, "Create") != 0) {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nType is not Create";
        write(client_socket, response, strlen(response));
    }

    yaml_parser_delete(&parser);
    close(client_socket);

    return 0;
}

int main() {
    int server_fd, new_socket;
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int check_payload(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int type_found = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            type_found = 1;
        } else if (event.type == YAML_SCALAR_EVENT && type_found && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -2;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int read_val = read(client_socket, buffer, BUFFER_SIZE);

    if (read_val > 0) {
        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 32\r\n\r\nError: Missing payload parameter.";
            write(client_socket, response, strlen(response));
        } else {
            payload_start += 8; // Skip "payload="
            if (strchr(payload_start, '&')) *strchr(payload_start, '&') = '\0';
            int check_result = check_payload(payload_start);
            if (check_result == -2) {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 35\r\n\r\nError: Create type is not allowed.";
                write(client_socket, response, strlen(response));
            } else {
                const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 8\r\n\r\nSuccess";
                write(client_socket, response, strlen(response));
            }
        }
    }

    close(client_socket);
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

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        handle_client(new_socket);
    }

    return 0;
}
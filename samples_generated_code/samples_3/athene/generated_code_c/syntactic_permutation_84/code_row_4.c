#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int client_socket, const char *message) {
    write(client_socket, message, strlen(message));
}

int parse_yaml(const char *payload, char **type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && !found_type) {
            *type = strdup((char *)event.data.scalar.value);
            found_type = 1;
        }
        yaml_event_delete(&event);
        if (found_type) break;
    }

    yaml_parser_delete(&parser);

    return found_type ? 0 : -1;
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *type = NULL;

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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        read(client_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send_response(client_socket, "Error: Payload parameter missing\n");
        } else {
            payload_start += 8; // skip "payload="
            char *payload_end = strchr(payload_start, '&');
            if (payload_end) *payload_end = '\0';

            if (parse_yaml(payload_start, &type) == 0 && strcmp(type, "Create") == 0) {
                send_response(client_socket, "Error: Type is Create\n");
            } else {
                send_response(client_socket, "Payload received and processed successfully\n");
            }

            free(type);
        }

        close(client_socket);
    }

    return 0;
}
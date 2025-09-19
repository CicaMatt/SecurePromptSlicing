#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    char *payload_start = strstr(buffer, "payload=");
    if (payload_start != NULL) {
        payload_start += strlen("payload=");
        char *payload_end = strchr(payload_start, '&');
        if (payload_end == NULL) {
            payload_end = payload_start + strlen(payload_start);
        }
        int len = payload_end - payload_start;
        char payload[len + 1];
        strncpy(payload, payload_start, len);
        payload[len] = '\0';

        yaml_parser_t parser;
        yaml_event_t event;
        if (!yaml_parser_initialize(&parser)) {
            close(client_socket);
            return;
        }
        yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

        while (1) {
            if (!yaml_parser_parse(&parser, &event)) {
                break;
            }

            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
                yaml_event_t value_event;
                if (yaml_parser_parse(&parser, &value_event) && value_event.type == YAML_SCALAR_EVENT) {
                    if (strcmp((char *)value_event.data.scalar.value, "Create") == 0) {
                        const char *error_message = "Error: Type is Create\n";
                        write(client_socket, error_message, strlen(error_message));
                    }
                }
            }

            yaml_event_delete(&event);
        }

        yaml_parser_delete(&parser);
    } else {
        const char *response = "No payload parameter found\n";
        write(client_socket, response, strlen(response));
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
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
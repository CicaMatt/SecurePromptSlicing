#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response;

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
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread <= 0) {
            close(new_socket);
            continue;
        }

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload parameter not found";
        } else {
            payload_start += strlen("payload=");
            yaml_parser_t parser;
            yaml_event_t event;
            char *payload_end = strchr(payload_start, '&');
            if (payload_end) {
                *payload_end = '\0';
            }

            if (!yaml_parser_initialize(&parser)) {
                response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nParser initialization failed";
            } else {
                yaml_parser_set_input_string(&parser, (const unsigned char *)payload_start, strlen(payload_start));
                int type_is_create = 0;
                while (!type_is_create && !yaml_parser_parse(&parser, &event)) {
                    if (event.type == YAML_SCALAR_EVENT) {
                        const char *value = (const char *)event.data.scalar.value;
                        if (strcmp(value, "Create") == 0) {
                            type_is_create = 1;
                        }
                    }
                    yaml_event_delete(&event);
                }
                yaml_parser_free(&parser);

                if (type_is_create) {
                    response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nType is Create, which is not allowed";
                } else {
                    response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest processed successfully";
                }
            }
        }

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}
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
        char *query_end = strchr(payload_start, '&');
        if (query_end != NULL) {
            *query_end = '\0';
        }

        yaml_parser_t parser;
        yaml_event_t event;
        if (!yaml_parser_initialize(&parser)) {
            close(client_socket);
            return;
        }
        yaml_parser_set_input_string(&parser, (unsigned char *)payload_start, strlen(payload_start));

        int is_create = 0;
        while (1) {
            if (!yaml_parser_parse(&parser, &event)) {
                break;
            }
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
                yaml_event_delete(&event);
                if (!yaml_parser_parse(&parser, &event)) {
                    break;
                }
                if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                    is_create = 1;
                }
            }
            yaml_event_delete(&event);
        }

        const char *response;
        if (is_create) {
            response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\n\r\nError: Create type not allowed";
        } else {
            response = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK";
        }

        write(client_socket, response, strlen(response));
    } else {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 13\r\n\r\nError: No payload";
        write(client_socket, response, strlen(response));
    }
    close(client_socket);
    yaml_parser_delete(&parser);
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
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
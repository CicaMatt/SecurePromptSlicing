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

int parse_yaml(char *buffer, char **type) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)buffer, strlen(buffer));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return -1;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (strcmp((char *)event.data.scalar.value, "type") == 0) {
                    if (!yaml_parser_parse(&parser, &event)) {
                        yaml_event_delete(&event);
                        yaml_parser_delete(&parser);
                        return -1;
                    }
                    *type = strdup((char *)event.data.scalar.value);
                }
                break;
            default:
                break;
        }

        yaml_event_delete(&event);
    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    const char *error_message = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type Create is not allowed.";

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);

        char *payload_start = strstr(buffer, "payload=");
        if (payload_start != NULL) {
            payload_start += strlen("payload=");
            char *end = strchr(payload_start, '&');
            if (end != NULL) {
                *end = '\0';
            }

            char *type;
            if (parse_yaml(payload_start, &type) == 0) {
                if (strcmp(type, "Create") == 0) {
                    send(new_socket, error_message, strlen(error_message), 0);
                    free(type);
                    close(new_socket);
                    continue;
                }
                free(type);
            }
        }

        send(new_socket, hello, strlen(hello), 0);
        close(new_socket);
    }

    return 0;
}
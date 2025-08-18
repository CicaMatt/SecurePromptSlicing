#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include "yaml.h"

void handle_client(int client_socket) {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        return;
    }

    // Parse HTTP request
    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, "\r\n");

    char query_string[1024] = {0};
    char *query_start = strstr(path, "?");
    if (query_start) {
        strcpy(query_string, query_start + 1);
    }

    // Check for payload parameter
    if (strstr(query_string, "payload=")) {
        char *payload_str = strchr(query_string, 'p') + strlen("payload=");
        yaml_parser_t parser;
        yaml_event_t event;

        if (!yaml_parser_initialize(&parser)) {
            fprintf(stderr, "Failed to initialize YAML parser!\n");
            close(client_socket);
            return;
        }

        yaml_parser_set_input_string(&parser, payload_str, strlen(payload_str));
        while (1) {
            if (!yaml_parser_parse(&parser, &event)) {
                fprintf(stderr, "Parser error %d\n", parser.error);
                break;
            }
            if (event.type == YAML_MAPPING_START_EVENT || event.type == YAML_SEQUENCE_START_EVENT) {
                yaml_event_delete(&event);
                continue;
            }

            if (event.type == YAML_SCALAR_EVENT) {
                if (strcmp((char *)event.data.scalar.value, "Create") == 0) {
                    char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nError: Create type not allowed";
                    send(client_socket, response, strlen(response), 0);
                    yaml_event_delete(&event);
                    break;
                }
            }

            yaml_event_delete(&event);

            if (event.type == YAML_STREAM_END_EVENT) {
                char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nSuccess";
                send(client_socket, response, strlen(response), 0);
                break;
            }
        }

        yaml_parser_delete(&parser);
    } else {
        char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\nError: No payload parameter";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int main() {
#ifdef __linux__
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return EXIT_FAILURE;
    }
#endif

    while (1) {
#ifdef __linux__
        int client_socket = accept(server_fd, NULL, NULL);

        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_socket);
#else
        printf("This example is designed for Linux.\n");
#endif
    }

#ifdef __linux__
    close(server_fd);
#endif

    return EXIT_SUCCESS;
}
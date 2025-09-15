#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "yaml.h"

#define PORT 5000

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received < 1) {
        close(client_socket);
        return;
    }

    const char *payload_param = "payload=";
    char *start = strstr(buffer, payload_param);

    if (!start) {
        const char *response = "Error: No payload parameter found.\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
        return;
    }

    start += strlen(payload_param);
    char *end_of_payload = strchr(start, '\r');
    if (!end_of_payload) {
        end_of_payload = strchr(start, '\n');
    }
    if (end_of_payload) {
        *end_of_payload = '\0';
    } else {
        close(client_socket);
        return;
    }

    yaml_parser_t parser;
    FILE *stream = fmemopen(start, strlen(start), "r");
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, stream);

    yaml_event_t event;
    if (!yaml_parser_parse(&parser, &event)) {
        const char *response = "Error: Failed to parse YAML.\n";
        send(client_socket, response, strlen(response), 0);
    } else {
        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp(event.data.scalar.value, "Create") == 0) {
                const char *response = "Error: Type 'Create' is not allowed.\n";
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *response = "Request processed successfully.\n";
                send(client_socket, response, strlen(response), 0);
            }
        }
    }

    yaml_event_delete(&event);
    yaml_parser_delete(&parser);
    fclose(stream);

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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}

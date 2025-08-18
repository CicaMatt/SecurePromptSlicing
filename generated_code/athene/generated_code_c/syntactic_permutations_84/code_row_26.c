#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *type_to_check) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) {
        return 0;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }
        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, type_to_check)) {
            found_type = 1;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return found_type;
}

int handle_request(char *buffer) {
    char payload[BUFFER_SIZE] = "";
    if (strstr(buffer, "payload=") == NULL) {
        return -1;
    } else {
        sscanf(buffer, "%*[^&]payload=%[^\n]", payload);
        if (!strcmp(payload, ";")) {
            if (parse_yaml(payload, "Create")) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        read(new_socket, buffer, BUFFER_SIZE);

        int result = handle_request(buffer);

        if (result == -1) {
            response = "HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nMissing payload parameter";
        } else if (result == 0) {
            response = "HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nPayload type is Create";
        }

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}
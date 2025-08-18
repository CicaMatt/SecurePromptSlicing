#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void parse_yaml(const char *payload, int client_socket) {
    yaml_parser_t parser;
    yaml_event_t event;
    const char *type = NULL;

    if (!yaml_parser_initialize(&parser)) {
        write(client_socket, "Error initializing YAML parser\n", 36);
        return;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event))
            break;

        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "type") == 0) {
            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) {
                break;
            }
            if (event.type == YAML_SCALAR_EVENT)
                type = (char *)event.data.scalar.value;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    if (type && strcmp(type, "Create") == 0) {
        write(client_socket, "Error: Type is Create\n", 23);
    } else {
        write(client_socket, "Payload parsed successfully\n", 26);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *payload;

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

    while(1) {
        printf("Listening on port %d...\n", PORT);
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        read(new_socket, buffer, BUFFER_SIZE);

        payload = strstr(buffer, "payload=");
        if (!payload) {
            write(new_socket, "Error: Missing payload parameter\n", 35);
            close(new_socket);
            continue;
        }

        payload += strlen("payload=");
        char *end = strchr(payload, '&');
        if (end) {
            *end = '\0';
        }

        parse_yaml(payload, new_socket);

        close(new_socket);
    }

    return 0;
}
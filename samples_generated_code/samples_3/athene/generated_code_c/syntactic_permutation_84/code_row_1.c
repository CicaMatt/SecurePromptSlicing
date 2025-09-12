#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *key) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (!found && !yaml_parser_parse(&parser, &event)) {
        if (event.type == YAML_SCALAR_EVENT && 
            strcmp((char *)event.data.scalar.value, key) == 0 &&
            event.data.scalar.tag->value == NULL) {

            yaml_event_delete(&event);
            if (!yaml_parser_parse(&parser, &event)) {
                found = 1;
            }
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);

    return found ? 1 : -1;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread > 0) {
        char *payload_start = strstr(buffer, "payload=");
        if (payload_start != NULL) {
            payload_start += strlen("payload=");
            char *end = strchr(payload_start, '&');
            if (end == NULL) end = strchr(payload_start, ' ');
            if (end != NULL) *end = '\0';

            if (parse_yaml(payload_start, "type: Create") == 1) {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\n\r\nError: Type 'Create' is not allowed";
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK";
            send(client_socket, response, strlen(response), 0);
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
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }
        handle_client(new_socket);
    }

    return 0;
}
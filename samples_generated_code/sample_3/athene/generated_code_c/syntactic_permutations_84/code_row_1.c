#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int parse_yaml(const char *payload, const char *expected_type) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_type = 0;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            yaml_parser_delete(&parser);
            return -1;
        }

        if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, expected_type)) {
            found_type = 1;
        }

        yaml_event_delete(&event);

        if (found_type || event.type == YAML_STREAM_END_EVENT) {
            break;
        }
    }

    yaml_parser_delete(&parser);
    return found_type ? 0 : -1;
}

int handle_request(int client_socket, char *request) {
    char payload[BUFFER_SIZE] = "";
    int content_length = 0;

    if (strstr(request, "payload=")) {
        sscanf(request, "%*[^&]&payload=%[^\r\n]", payload);
        if (parse_yaml(payload, "Create") == 0) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 29\r\n\r\nError: Create type is not allowed";
            send(client_socket, response, strlen(response), 0);
            return -1;
        }
    }

    if (strlen(payload) == 0) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 25\r\n\r\nError: Payload parameter missing";
        send(client_socket, response, strlen(response), 0);
        return -1;
    }

    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nRequest accepted";
    send(client_socket, response, strlen(response), 0);
    return 0;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(client_fd, buffer, BUFFER_SIZE - 1);

        handle_request(client_fd, buffer);

        close(client_fd);
    }

    return 0;
}
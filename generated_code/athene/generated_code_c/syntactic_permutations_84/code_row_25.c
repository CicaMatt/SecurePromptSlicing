#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int sockfd, const char *msg) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    write(sockfd, response, strlen(response));
    write(sockfd, msg, strlen(msg));
}

int handle_request(char *buffer) {
    char *payload = strstr(buffer, "payload=");
    if (!payload) {
        return -1;
    }

    payload += 8; // skip "payload="

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        return -1;
    }

    if (yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload))) {
        while (1) {
            if (!yaml_parser_parse(&parser, &event)) {
                break;
            }
            if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
                yaml_event_delete(&event);
                yaml_parser_free(&parser);
                return -1;
            }
            yaml_event_delete(&event);
        }
    }

    yaml_parser_free(&parser);
    return 0;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);

        if (handle_request(buffer) == -1) {
            send_response(new_socket, "Error: Invalid request or payload type is Create.\n");
        } else {
            send_response(new_socket, "Success!\n");
        }

        close(new_socket);
    }

    return 0;
}
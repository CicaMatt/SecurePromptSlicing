#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <yaml.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void send_response(int sockfd, const char *message) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s";
    int len = snprintf(NULL, 0, response, strlen(message), message);
    char *buf = malloc(len + 1);
    sprintf(buf, response, strlen(message), message);
    send(sockfd, buf, len, 0);
    free(buf);
}

int is_create(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;
    int found_create = 0;

    if (!yaml_parser_initialize(&parser)) return -1;
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload));

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) break;
        if (event.type == YAML_SCALAR_EVENT && strcmp((char *)event.data.scalar.value, "Create") == 0) {
            found_create = 1;
            break;
        }
        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    return found_create;
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

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        int n = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (n <= 0) continue;

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send_response(new_socket, "Error: Missing payload parameter");
            close(new_socket);
            continue;
        }

        payload_start += strlen("payload=");
        char *end = strchr(payload_start, '&');
        if (end) *end = '\0';

        if (is_create(payload_start)) {
            send_response(new_socket, "Error: Payload contains 'Create'");
        } else {
            send_response(new_socket, "Payload processed successfully");
        }

        close(new_socket);
    }

    return 0;
}
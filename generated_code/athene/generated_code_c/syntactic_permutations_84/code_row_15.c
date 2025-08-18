#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

typedef struct {
    char *type;
} Payload;

int parse_yaml(const char *yaml, Payload *payload) {
    // Simplified YAML parsing (not robust for all cases)
    char type_key[] = "type: ";
    size_t key_len = strlen(type_key);
    if (strstr(yaml, type_key)) {
        const char *type_start = yaml + key_len;
        const char *type_end = strchr(type_start, '\n');
        if (!type_end) type_end = type_start + strlen(type_start);
        size_t len = type_end - type_start;
        payload->type = malloc(len + 1);
        strncpy(payload->type, type_start, len);
        payload->type[len] = '\0';
        return 1;
    }
    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    if (strstr(buffer, "payload=")) {
        const char *payload_start = strstr(buffer, "payload=") + strlen("payload=");
        size_t payload_len = strcspn(payload_start, "&\r\n");

        char payload_str[payload_len + 1];
        strncpy(payload_str, payload_start, payload_len);
        payload_str[payload_len] = '\0';

        Payload payload;
        if (parse_yaml(payload_str, &payload)) {
            if (strcmp(payload.type, "Create") == 0) {
                const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Type is Create";
                send(client_socket, response, strlen(response), 0);
            } else {
                const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nSuccess";
                send(client_socket, response, strlen(response), 0);
            }
            free(payload.type);
        } else {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid payload format";
            send(client_socket, response, strlen(response), 0);
        }
    } else {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter";
        send(client_socket, response, strlen(response), 0);
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
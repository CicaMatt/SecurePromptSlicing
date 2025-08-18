#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    const char *payload_start = strstr(request, "payload=");
    if (payload_start == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 22\r\nConnection: close\r\n\r\nNo payload parameter found.\n");
        return;
    }

    payload_start += 8; // Move past "payload="
    const char *payload_end = strstr(payload_start, "\r\n");

    if (payload_end == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 22\r\nConnection: close\r\n\r\nMalformed request.\n");
        return;
    }

    size_t payload_length = payload_end - payload_start;
    char *payload = malloc(payload_length + 1);
    if (payload == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        return;
    }

    strncpy(payload, payload_start, payload_length);
    payload[payload_length] = '\0';

    // Check if the type is Create
    char *type_start = strstr(payload, "type:");
    if (type_start != NULL) {
        type_start += 5; // Move past "type:"
        char expected_type[] = "Create";
        while (*type_start == ' ') type_start++; // Skip spaces

        size_t type_length = strlen(type_start);
        if (strncmp(type_start, expected_type, type_length) == 0 && type_start[type_length] == '\n') {
            printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 28\r\nConnection: close\r\n\r\nType Create is not allowed.\n");
        } else {
            printf("HTTP/1.1 200 OK\r\nContent-Length: 0\r\nConnection: close\r\n\r\n");
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 22\r\nConnection: close\r\n\r\nType not found.\n");
    }

    free(payload);
}

void start_server() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    listen(server_socket, 5);

    addr_size = sizeof(client_addr);

    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size))) {
        char buffer[BUFFER_SIZE];
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("Receive failed");
            close(client_socket);
            continue;
        }

        buffer[bytes_received] = '\0';
        handle_request(buffer);

        close(client_socket);
    }

    if (client_socket < 0) {
        perror("Accept failed");
        close(server_socket);
    }

    close(server_socket);
}

int main() {
    start_server();
    return 0;
}
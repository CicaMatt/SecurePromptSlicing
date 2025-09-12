#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

typedef struct {
    char *name;
} Create;

int contains_payload(const char *request) {
    return strstr(request, "payload=") != NULL;
}

Create parse_payload(const char *request) {
    const char *start = strstr(request, "payload=");
    if (start == NULL) return (Create){NULL};
    start += 8; // Skip "payload="
    char *end = strchr(start, '&');
    size_t len = end ? (size_t)(end - start) : strlen(start);
    Create create;
    create.name = malloc(len + 1);
    strncpy(create.name, start, len);
    create.name[len] = '\0';
    return create;
}

void send_response(int client_socket, const char *message) {
    write(client_socket, message, strlen(message));
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

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, BUFFER_SIZE);

        if (!contains_payload(buffer)) {
            send_response(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload parameter missing.\r\n");
            close(new_socket);
            continue;
        }

        Create create = parse_payload(buffer);
        if (create.name == NULL || strlen(create.name) == 0) {
            send_response(new_socket, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid payload.\r\n");
        } else {
            free(create.name);
            send_response(new_socket, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload received successfully.\r\n");
        }

        close(new_socket);
    }

    return 0;
}
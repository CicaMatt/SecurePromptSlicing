#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

typedef struct {
    char *type;
} Create;

int parse_payload(char *payload, Create *create) {
    if (strstr(payload, "type=Create")) {
        create->type = "Create";
        return 1;
    }
    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);
    
    char *query_start = strstr(buffer, "?");
    if (query_start == NULL || strstr(query_start, "payload") == NULL) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload parameter missing";
        write(client_socket, response, strlen(response));
        close(client_socket);
        return;
    }

    Create create;
    if (parse_payload(query_start, &create)) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Payload type is Create";
        write(client_socket, response, strlen(response));
    } else {
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload received and processed";
        write(client_socket, response, strlen(response));
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
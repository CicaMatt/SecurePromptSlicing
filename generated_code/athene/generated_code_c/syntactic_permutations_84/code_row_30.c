#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE);

    char *payload = NULL;
    if (strstr(buffer, "payload=")) {
        payload = strstr(buffer, "payload=");
        payload += strlen("payload=");
        if (strchr(payload, '&')) *strchr(payload, '&') = '\0';
    }

    if (!payload) {
        const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=UTF-8\r\nContent-Length: 36\r\nConnection: close\r\n\r\nPayload parameter is missing.";
        send(client_socket, response, strlen(response), 0);
    } else {
        if (strcmp(payload, "Create") == 0) {
            const char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain; charset=UTF-8\r\nContent-Length: 32\r\nConnection: close\r\n\r\nPayload type 'Create' is not allowed.";
            send(client_socket, response, strlen(response), 0);
        } else {
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nContent-Length: 27\r\nConnection: close\r\n\r\nPayload received successfully.";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_request(client_fd);
    }

    close(server_fd);
    return 0;
}
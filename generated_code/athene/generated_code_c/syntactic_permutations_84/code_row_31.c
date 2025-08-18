#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response_400 = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\nPayload parameter is missing";
    const char *response_403 = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/plain\r\nContent-Length: 28\r\n\r\nInvalid payload type: Create";

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
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE);
        char *payload_param = strstr(buffer, "payload=");
        if (!payload_param) {
            send(new_socket, response_400, strlen(response_400), 0);
        } else {
            payload_param += 8; // skip "payload="
            char *end_of_value = strchr(payload_param, '&');
            if (end_of_value) *end_of_value = '\0';
            if (strcmp(payload_param, "Create") == 0) {
                send(new_socket, response_403, strlen(response_403), 0);
            } else {
                const char *response_ok = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 8\r\n\r\nPayload OK";
                send(new_socket, response_ok, strlen(response_ok), 0);
            }
        }

        close(new_socket);
    }

    return 0;
}
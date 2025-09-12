#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *err_msg_no_payload = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 23\r\n\r\nError: No payload parameter found.\r\n";
    const char *err_msg_invalid_type = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 28\r\n\r\nError: Invalid type in payload.\r\n";

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int valread = read(new_socket, buffer, BUFFER_SIZE);

        char *payload_start = strstr(buffer, "payload=");
        if (!payload_start) {
            send(new_socket, err_msg_no_payload, strlen(err_msg_no_payload), 0);
            close(new_socket);
            continue;
        }

        payload_start += 8; // Move past "payload="
        char *end_of_payload = strchr(payload_start, '&');
        int payload_length = end_of_payload ? (end_of_payload - payload_start) : strlen(payload_start);

        if (strncmp(payload_start, "Create", payload_length) == 0) {
            send(new_socket, err_msg_invalid_type, strlen(err_msg_invalid_type), 0);
        } else {
            const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nPayload received.\r\n";
            send(new_socket, response, strlen(response), 0);
        }

        close(new_socket);
    }

    return 0;
}
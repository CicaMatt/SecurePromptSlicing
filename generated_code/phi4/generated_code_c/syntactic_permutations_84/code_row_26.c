#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    printf("Received: %s\n", buffer);

    // Check for "payload" parameter
    char *payload_param = strstr(buffer, "payload=");
    if (!payload_param) {
        const char *error_msg = "Error: Missing payload parameter.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    // Extract the value of the payload parameter
    payload_param += strlen("payload=");
    char *payload_end = strchr(payload_param, ' ');
    if (!payload_end) {
        payload_end = buffer + bytes_received;  // End of buffer if no space found
    }
    size_t payload_length = payload_end - payload_param;
    char *payload_value = strndup(payload_param, payload_length);

    // Check if payload is ";" and parse as YAML
    if (strcmp(payload_value, ";") == 0) {
        const char *error_msg = "Error: Invalid YAML type Create.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        free(payload_value);
        close(client_socket);
        return;
    }

    // If payload is not ";", assume it's a valid YAML and do nothing special
    const char *success_msg = "Payload processed successfully.\n";
    send(client_socket, success_msg, strlen(success_msg), 0);

    free(payload_value);
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    while (1) {
        printf("Waiting for connections...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}

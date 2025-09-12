#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 2048

typedef struct {
    char type[10];
} Payload;

void handle_request(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received < 0) {
        perror("recv");
        close(client_fd);
        return;
    }

    buffer[bytes_received] = '\0';

    char *payload_str = strstr(buffer, "payload=");
    if (!payload_str) {
        const char *error_msg = "Error: Payload parameter is missing.\n";
        send(client_fd, error_msg, strlen(error_msg), 0);
    } else {
        payload_str += 8; // Skip past 'payload='

        Payload payload;
        memset(&payload, 0, sizeof(Payload));
        strncpy(payload.type, payload_str, sizeof(payload.type) - 1);

        if (strcmp(payload.type, "Create") == 0) {
            const char *error_msg = "Error: Type is Create.\n";
            send(client_fd, error_msg, strlen(error_msg), 0);
        } else {
            const char *response = "Payload received successfully.\n";
            send(client_fd, response, strlen(response), 0);
        }
    }

    close(client_fd);
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

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);
    }

    return 0;
}
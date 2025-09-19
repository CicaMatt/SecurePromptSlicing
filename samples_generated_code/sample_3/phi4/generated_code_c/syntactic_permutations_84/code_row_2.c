#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_request(int client_socket) {
    char buffer[4096];
    int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }
    
    buffer[bytes_read] = '\0';
    char *payload_str = strstr(buffer, "payload=");
    if (!payload_str) {
        const char *error_msg = "Error: Missing payload parameter.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }

    payload_str += 8; // Move past "payload="
    char payload[4096] = {0};
    strncpy(payload, payload_str, sizeof(payload) - 1);

    if (strcmp(payload, ";") == 0) {
        const char *yaml_header = "---\ntype: Create\n";
        
        if (strncmp(yaml_header, payload, strlen(yaml_header)) == 0) {
            const char *error_msg = "Error: Payload type is 'Create'.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            const char *success_msg = "Payload processed successfully.\n";
            send(client_socket, success_msg, strlen(success_msg), 0);
        }
    } else {
        const char *error_msg = "Error: Invalid payload format.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

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
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);
    }

    close(server_fd);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_connection(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0) {
        printf("Error receiving data.\n");
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    char *payload_start = strstr(buffer, "payload=");
    
    if (!payload_start) {
        const char *error_msg = "Bad Request: Payload missing.";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }
    
    payload_start += 8; // Move past 'payload='
    char *yaml_end = strstr(payload_start, "\r\n");
    if (!yaml_end) {
        const char *error_msg = "Bad Request: Invalid YAML format.";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }
    
    *yaml_end = '\0'; // Null-terminate the YAML payload
    printf("YAML Payload:\n%s\n", payload_start);

    // Check if type is Create
    if (strstr(payload_start, "type: Create") != NULL) {
        const char *error_msg = "Forbidden: Type 'Create' not allowed.";
        send(client_socket, error_msg, strlen(error_msg), 0);
        close(client_socket);
        return;
    }
    
    // If no issues found
    const char *success_msg = "Request processed successfully.";
    send(client_socket, success_msg, strlen(success_msg), 0);

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        
        handle_connection(client_socket);
    }

    close(server_fd);
    return 0;
}
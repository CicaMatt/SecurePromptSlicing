#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char *type;
} Payload;

void handle_client(int client_socket) {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        
        // Check for payload parameter
        char *payload_pos = strstr(buffer, "payload=");
        if (!payload_pos) {
            const char *error_message = "Error: No payload parameter found.\n";
            send(client_socket, error_message, strlen(error_message), 0);
        } else {
            payload_pos += 8; // Move past 'payload='
            
            // Check the type within the payload
            Payload payload;
            sscanf(payload_pos, "%ms", &payload.type);

            if (strcmp(payload.type, "Create") == 0) {
                const char *error_message = "Error: Payload type is Create.\n";
                send(client_socket, error_message, strlen(error_message), 0);
            } else {
                const char *success_message = "Payload received successfully.\n";
                send(client_socket, success_message, strlen(success_message), 0);
            }

            free(payload.type);
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set server address to listen on any IP and port 5000
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for client connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        
        handle_client(new_socket);
        close(new_socket);
    }

    return 0;
}
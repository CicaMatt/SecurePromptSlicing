#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        printf("Request: %s\n", buffer);

        // Check if request is valid
        if (!strstr(buffer, "GET / HTTP/1.1")) {
            char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request";
            send(client_socket, error_response, strlen(error_response), 0);
            return;
        }

        // Check for payload parameter
        if (strstr(buffer, "payload=")) {
            char *start = strstr(buffer, "payload=");
            start += 8; // Move to the actual payload

            // Simulate YAML parsing and type checking
            char payload[1024] = {0};
            strncpy(payload, start, strlen(start));
            
            // For simplicity, assume payload is a simple string with "type: Create"
            if (strstr(payload, "type: Create")) {
                char *error_response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nCreate type not allowed";
                send(client_socket, error_response, strlen(error_response), 0);
                return;
            }
        }

        // Default response for valid GET request
        char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
        send(client_socket, response, strlen(response), 0);
    } else {
        printf("Connection closed by client.\n");
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

    // Forcefully attaching socket to the port 5000
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

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_request(int client_sock) {
    char buffer[1024] = {0};
    int valread = read(client_sock, buffer, sizeof(buffer));
    
    if (valread > 0) {
        // Check for the presence of "payload" parameter
        if (strstr(buffer, "payload=")) {
            char *payload_start = strstr(buffer, "payload=");
            if (payload_start != NULL) {
                payload_start += 8; // Move past "payload="
                
                // Simulate YAML parsing and type checking
                // In a real application, you would use a YAML library like libyaml here.
                // For this example, we'll assume the payload is simple text.
                char *type_marker = strstr(payload_start, "type: Create");
                if (type_marker != NULL) {
                    const char *error_msg = "Error: Type 'Create' not allowed.\n";
                    send(client_sock, error_msg, strlen(error_msg), 0);
                } else {
                    const char *success_msg = "Payload processed successfully.\n";
                    send(client_sock, success_msg, strlen(success_msg), 0);
                }
            }
        } else {
            const char *error_msg = "Error: 'payload' parameter is missing.\n";
            send(client_sock, error_msg, strlen(error_msg), 0);
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 5000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 5000
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
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

        close(new_socket);
    }

    return 0;
}
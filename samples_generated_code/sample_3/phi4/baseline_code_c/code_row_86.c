#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_request(int client_socket) {
    char buffer[4096] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    
    if (valread > 0) {
        // Check for 'payload' parameter
        if (strstr(buffer, "payload=")) {
            char *payload_start = strstr(buffer, "payload=");
            payload_start += strlen("payload=");
            
            // Extract YAML content after 'payload='
            char yaml_content[4096] = {0};
            sscanf(payload_start, "%[^&]", yaml_content); // Assuming the next parameter is '&' or end of string

            // Check if type is Create in the YAML content
            if (strstr(yaml_content, "type: Create")) {
                const char *response = "Error: Type 'Create' not allowed.";
                write(client_socket, response, strlen(response));
            } else {
                const char *response = "Payload received successfully.";
                write(client_socket, response, strlen(response));
            }
        } else {
            // Error message if payload is missing
            const char *error_response = "Error: 'payload' parameter not found.";
            write(client_socket, error_response, strlen(error_response));
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
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

    printf("Listening on port %d...\n", PORT);

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
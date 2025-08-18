#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_request(int client_sock) {
    char buffer[1024] = {0};
    int valread = read(client_sock, buffer, sizeof(buffer));
    
    if (valread > 0) {
        printf("Received request: %s\n", buffer);
        
        // Check for payload in the request
        const char *payload_str = "payload=";
        size_t payload_len = strlen(payload_str);

        char *payload_pos = strstr(buffer, payload_str);
        if (!payload_pos || payload_pos == buffer) {
            write(client_sock, "Error: Missing payload parameter.\n", 37);
            return;
        }

        // Extract the YAML payload
        payload_pos += payload_len;
        char *end_of_payload = strchr(payload_pos, ' ');
        size_t payload_size = end_of_payload ? (size_t)(end_of_payload - payload_pos) : strlen(payload_pos);
        
        char yaml_buffer[payload_size + 1];
        strncpy(yaml_buffer, payload_pos, payload_size);
        yaml_buffer[payload_size] = '\0';

        // Parse YAML and check for type
        if (strstr(yaml_buffer, "type: Create") != NULL) {
            write(client_sock, "Error: Type 'Create' is not allowed.\n", 40);
            return;
        }

        // If everything is okay, respond with success message
        write(client_sock, "Request processed successfully!\n", 31);
    }
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
    
    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_request(new_socket);
        
        close(new_socket);
    }
    
    return 0;
}
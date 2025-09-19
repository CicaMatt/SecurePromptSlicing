#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

void handle_client(int client_socket) {
    char buffer[1024] = {0};
    int read_size;

    // Receive data from the client
    if ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) == -1) {
        perror("recv");
        close(client_socket);
        return;
    }

    buffer[read_size] = '\0';
    
    char *payload_start = strstr(buffer, "payload=");

    if (!payload_start) {
        const char *error_msg = "Error: Missing payload parameter.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
    } else {
        payload_start += 8; // Move past 'payload='
        
        char *payload_end = strchr(payload_start, '&');
        if (payload_end) {
            *payload_end = '\0';
        }

        const char *yaml_content = payload_start;
        const char *type_create_check = "type: Create";

        if (strstr(yaml_content, type_create_check)) {
            const char *error_msg = "Error: Type cannot be 'Create'.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            // If no errors, acknowledge the payload
            const char *success_msg = "Payload received successfully.\n";
            send(client_socket, success_msg, strlen(success_msg), 0);
        }
    }

    close(client_socket);
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
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while ((new_socket = accept(server_fd,
                                (struct sockaddr *)&address,
                                (socklen_t*)&addrlen))) {

        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
    }

    if (new_socket == -1) {
        perror("accept");
    }

    close(server_fd);

    return 0;
}
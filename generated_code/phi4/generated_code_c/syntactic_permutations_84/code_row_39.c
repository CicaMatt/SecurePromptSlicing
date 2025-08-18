#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE] = {0};
    
    // Read data from the client
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
    if (bytes_received < 1) {
        close(client_sock);
        return;
    }
    
    // Check for "payload" parameter in the request
    char *payload_pos = strstr(buffer, "payload=");
    if (!payload_pos || bytes_received <= strlen("payload=")) {
        send(client_sock, "No payload", 11, 0);
        close(client_sock);
        return;
    }
    
    // Extract and parse the YAML content from payload parameter
    payload_pos += strlen("payload=");
    char *yaml_end = strstr(payload_pos, "&");
    if (!yaml_end) {
        yaml_end = buffer + bytes_received;
    }
    
    // Simulate parsing the YAML to check for type "Create"
    // In a real-world scenario, use a YAML parser library
    size_t yaml_length = yaml_end - payload_pos;
    char *type_start = strstr(payload_pos, "type: Create");
    
    if (type_start && (type_start + strlen("type: Create") <= yaml_end)) {
        send(client_sock, "Type is Create", 15, 0);
    } else {
        send(client_sock, "Not a Create type", 17, 0);
    }
    
    close(client_sock);
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

    // Bind the socket to the port 5000
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
    
    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd,
                                 (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        
        handle_client(new_socket);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5000
#define BUFFER_SIZE 4096

// Function to parse payload and check for type "."
int check_yaml_payload(const char *payload) {
    // Simple YAML parsing logic (only checks if payload contains "type: .")
    const char *type_marker = "type: .";
    return strstr(payload, type_marker) != NULL;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        return;
    }
    
    buffer[bytes_received] = '\0';
    printf("Received: %s\n", buffer);

    // Check for "payload" parameter in the request
    char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        const char *error_message = "Error: Missing payload parameter.\n";
        send(client_socket, error_message, strlen(error_message), 0);
        close(client_socket);
        return;
    }

    // Extract the actual payload value
    payload_start += strlen("payload="); // Move pointer to start of the actual payload
    char *payload_end = strchr(payload_start, '&'); // Assuming '&' is used as a delimiter
    if (!payload_end) {
        payload_end = buffer + bytes_received; // End of buffer if no '&' found
    }
    
    size_t payload_length = payload_end - payload_start;
    char *actual_payload = malloc(payload_length + 1);
    strncpy(actual_payload, payload_start, payload_length);
    actual_payload[payload_length] = '\0';

    if (check_yaml_payload(actual_payload)) {
        const char *error_message = "Error: Invalid YAML type.\n";
        send(client_socket, error_message, strlen(error_message), 0);
    } else {
        const char *success_message = "Payload processed successfully.\n";
        send(client_socket, success_message, strlen(success_message), 0);
    }

    free(actual_payload);
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}
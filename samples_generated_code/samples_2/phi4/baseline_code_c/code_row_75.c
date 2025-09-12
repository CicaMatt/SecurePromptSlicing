#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_client(int client_fd) {
    char buffer[1024] = {0};
    int bytes_received;
    
    // Receive data from the client
    bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received < 1) {
        close(client_fd);
        return;
    }

    // Extract payload parameter from URL
    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        printf("Payload not found\n");
        close(client_fd);
        return;
    }
    payload_start += strlen("payload=");

    // Find the end of the payload value (either by space or end of line)
    const char *payload_end = strchr(payload_start, ' ');
    if (!payload_end) {
        payload_end = buffer + bytes_received;
    }

    size_t payload_length = payload_end - payload_start;
    char *payload_value = malloc(payload_length + 1);
    strncpy(payload_value, payload_start, payload_length);
    payload_value[payload_length] = '\0';

    // Simulate loading payload into a dictionary and returning the "name" value
    const char *response_key = "name";
    const char *response_value = "John Doe"; // Example name

    // Prepare response
    char response[1024];
    snprintf(response, sizeof(response), 
             "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", response_value);

    send(client_fd, response, strlen(response), 0);
    close(client_fd);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
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

    printf("Server listening on port %d\n", PORT);

    while (1) {
        int client_fd;
        struct sockaddr_in client_address;

        // Accept a connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_fd);
    }
    
    close(server_fd);
    return 0;
}
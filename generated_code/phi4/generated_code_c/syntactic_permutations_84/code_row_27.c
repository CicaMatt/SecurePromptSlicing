#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PORT 5000

void handle_request(const char *request) {
    char *payload_start = strstr(request, "payload=");
    if (payload_start == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Missing payload parameter.\r\n");
        return;
    }

    payload_start += 8; // Skip 'payload='
    char *payload_end = strstr(payload_start, "\n");

    if (payload_end != NULL) {
        size_t payload_len = payload_end - payload_start;
        char *payload = malloc(payload_len + 1);
        strncpy(payload, payload_start, payload_len);
        payload[payload_len] = '\0';

        // Check for Create type
        if (strstr(payload, "type: Create") != NULL) {
            printf("HTTP/1.1 403 Forbidden\r\nContent-Type: text/plain\r\n\r\nError: 'Create' type is not allowed.\r\n");
        } else {
            printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPayload received successfully.\r\n");
        }

        free(payload);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nError: Invalid payload format.\r\n");
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
    
    // Listen for incoming connections
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

        char buffer[1024] = {0};
        read(new_socket, buffer, sizeof(buffer));
        
        handle_request(buffer);

        close(new_socket);
    }
    
    return 0;
}


**Note:** This is a simple example and not suitable for production use. For real-world applications, consider using libraries like `libevent`, `libuv` or frameworks such as `mongoose` that provide more robust features and security.
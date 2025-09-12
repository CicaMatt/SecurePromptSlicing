#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void handle_client(int client_fd) {
    char buffer[1024];
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        
        // Check if the request is for /api
        const char *path = "/api";
        if (strncmp(buffer, "GET ", 4) == 0 && strstr(buffer, path) != NULL) {
            char *payload_str = strstr(buffer, "payload=");
            
            if (payload_str) {
                payload_str += strlen("payload=");
                
                // Parse the payload
                size_t len = strcspn(payload_str, " ");
                char *payload = strndup(payload_str, len);
                
                // Simulate loading into a dictionary and finding the name value
                const char *name_value = "";
                if (strcmp(payload, "key1") == 0) {
                    name_value = "value1";
                } else if (strcmp(payload, "key2") == 0) {
                    name_value = "value2";
                }
                
                // Construct response
                char response[1024];
                snprintf(response, sizeof(response), 
                         "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", name_value);
                
                send(client_fd, response, strlen(response), 0);
            } else {
                char *response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nPayload not found";
                send(client_fd, response, strlen(response), 0);
            }
            
            free(payload);
        } else {
            char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nRoute not found";
            send(client_fd, response, strlen(response), 0);
        }
    }

    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to reuse the port
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to the port
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
        client_fd = accept(server_fd, (struct sockaddr *)&address, &addr_len);
        
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_fd);
    }

    close(server_fd);
    return 0;
}
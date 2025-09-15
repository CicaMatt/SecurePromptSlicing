#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Include yaml-cpp library header
#include <yaml-cpp/yaml.h>

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1023);
    
    if (valread > 0) {
        // Check if "payload=" is present in the request
        char *payload_str = strstr(buffer, "payload=");
        if (!payload_str) {
            const char *error_msg = "Error: payload parameter not found.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            // Extract and parse YAML
            payload_str += strlen("payload="); // Move past 'payload=' to get the actual data
            YAML::Node yaml_node = YAML::Load(payload_str);

            if (!yaml_node["type"].IsDefined() || strcmp(yaml_node["type"].as<std::string>().c_str(), "Create") != 0) {
                const char *success_msg = "Payload processed successfully.\n";
                send(client_socket, success_msg, strlen(success_msg), 0);
            } else {
                const char *error_msg = "Error: Type is Create.\n";
                send(client_socket, error_msg, strlen(error_msg), 0);
            }
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
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

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

    while (1) {
        printf("Waiting for a connection...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_request(new_socket);
    }

    close(server_fd);

    return 0;
}

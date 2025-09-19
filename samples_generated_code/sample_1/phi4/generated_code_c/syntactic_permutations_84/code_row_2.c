#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
import <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// A very simple YAML parser for demonstration purposes only.
typedef enum { kTypeCreate, kTypeUnknown } PayloadType;

PayloadType parse_yaml_payload(const char *yaml) {
    if (strncmp(yaml, "---\ntype: Create\n", 15) == 0) {
        return kTypeCreate;
    }
    return kTypeUnknown;
}

const char *parse_request(int client_socket) {
    char buffer[4096];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 1) {
        return "Error: Request not received.";
    }

    // Parse request for payload parameter
    const char *payload_start = strstr(buffer, "payload=");
    if (!payload_start) {
        return "Error: No 'payload' parameter found in the request.";
    }
    
    payload_start += 8; // Move past "payload="
    char *end_of_payload = strchr(payload_start, '&');
    if (end_of_payload) {
        *end_of_payload = '\0'; // Null-terminate the YAML string
    }

    return payload_start;
}

void handle_client(int client_socket) {
    const char *payload = parse_request(client_socket);
    
    if (strncmp(payload, "Error:", 6) == 0) {
        send(client_socket, payload, strlen(payload), 0);
    } else {
        PayloadType type = parse_yaml_payload(payload);
        if (type == kTypeCreate) {
            char *response = "Error: Type 'Create' is not allowed.";
            send(client_socket, response, strlen(response), 0);
        } else {
            char *response = "Payload processed successfully.";
            send(client_socket, response, strlen(response), 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

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
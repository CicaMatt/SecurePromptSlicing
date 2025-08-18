#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000

typedef struct {
    char *type;
} Payload;

Payload parse_yaml(const char *yaml_str) {
    Payload payload = {NULL};
    if (strstr(yaml_str, "type: Create") != NULL) {
        payload.type = strdup("Create");
    }
    return payload;
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received < 1) {
        close(client_socket);
        return;
    }

    const char *payload_param = "payload=";
    char *payload_start = strstr(buffer, payload_param);
    
    if (!payload_start) {
        const char *error_msg = "Error: No payload parameter found.\n";
        send(client_socket, error_msg, strlen(error_msg), 0);
    } else {
        payload_start += strlen(payload_param);
        
        Payload payload = parse_yaml(payload_start);
        
        if (strcmp(payload.type, "Create") == 0) {
            const char *error_msg = "Error: Operation type 'Create' is not allowed.\n";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            const char *success_msg = "Payload processed successfully.\n";
            send(client_socket, success_msg, strlen(success_msg), 0);
        }
        
        free(payload.type);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);
    }

    return 0;
}
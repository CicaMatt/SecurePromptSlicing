#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// YAML parsing function prototypes
int parse_yaml(const char *yaml_str, const char **type);
const char* get_yaml_value(const char *yaml_str, const char *key);

#define PORT 5000
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    
    const char *payload_key = "payload=";
    char *payload_start = strstr(buffer, payload_key);

    if (payload_start != NULL) {
        payload_start += strlen(payload_key); // Move to the start of the payload value
        char *payload_end = strchr(payload_start, ' ');
        if (payload_end == NULL) {
            payload_end = buffer + bytes_received;
        }

        char yaml_str[buffer_size - (payload_start - buffer)];
        strncpy(yaml_str, payload_start, payload_end - payload_start);
        yaml_str[payload_end - payload_start] = '\0';

        const char *type = NULL;
        if (parse_yaml(yaml_str, &type) == 0 && strcmp(type, "Create") == 0) {
            const char *error_msg = "Error: Create type is not allowed";
            send(client_socket, error_msg, strlen(error_msg), 0);
        } else {
            const char *response = "Request processed successfully";
            send(client_socket, response, strlen(response), 0);
        }
    } else {
        const char *response = "No payload found";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
}

int parse_yaml(const char *yaml_str, const char **type) {
    // Simplified YAML parsing for demonstration purposes
    if (strstr(yaml_str, "type: Create")) {
        *type = "Create";
        return 0;
    }
    return -1; // Parsing failed or type not found
}

const char* get_yaml_value(const char *yaml_str, const char *key) {
    // Simplified function to demonstrate YAML key-value extraction
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}